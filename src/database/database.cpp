#include "database.h"
#include <stdio.h>
#include <string>
#include <cstring>
#include <utility>

column_key* SQLColumns::getValuePtr(std::string key) {
	if (key == "id") {
		return &id;
	}
	return nullptr;
}

void SQLColumns::update(char* key, char* value) {
	std::string key_string = std::string(key);
	column_key* value_ptr = getValuePtr(key_string);
	if (value_ptr == nullptr) {
		fprintf(stderr, "SQL unidentified key %s for %s", key, typeid(this).name());
	} else {
		*value_ptr = std::make_unique<std::string>(value);
	}
}

column_key* Citizen::getValuePtr(std::string key) {
	if (key == "age") {
		return &age;	
	} else if (key == "first_name") {
		return &first_name;
	} else if (key == "last_name") {
		return &last_name;
	} else if (key == "income") {
		return &income;
	} else if (key == "household_id") {
		return &household_id;
	} else if (key == "spouse_id") {
		return &spouse_id;
	}
	return SQLColumns::getValuePtr(key);
}

column_key* Household::getValuePtr(std::string key) {
	if (key == "family_status") {
		return &family_status;
	} else if (key == "zip") {
		return &zip;
	}
	return SQLColumns::getValuePtr(key);
}

CitizenDatabase::CitizenDatabase(const char* filename) {
	int rc = sqlite3_open(filename, &database);
	if (rc) {
		fprintf(stderr, "Could not open database: %s", sqlite3_errmsg(database));
	}
}

template<class T>
static int query_callback(void* columns, int argc, char** argv, char** azColName) {

	std::shared_ptr<T> column(new T());
	for (int i = 0; i < argc; i++) {
		column->update(azColName[i], argv[i]);
	}

	std::vector<std::shared_ptr<T>>* cols = (std::vector<std::shared_ptr<T>>*)(columns);
	cols->push_back(column);
	return 0;
}

template<class T> requires std::derived_from<T, SQLColumns>
std::vector<std::shared_ptr<T>> CitizenDatabase::Query(const char *query_text) {
	char *errMessage = 0;

	std::vector<std::shared_ptr<T>> out = std::vector<std::shared_ptr<T>>();

	int code = sqlite3_exec(database, query_text, query_callback<T>, &out, &errMessage);
	if (code != SQLITE_OK) {
		fprintf(stderr, "SQL query error: %s", errMessage);
		sqlite3_free(errMessage);
	}
	return out;
}

template std::vector<std::shared_ptr<Household>> CitizenDatabase::Query<Household>(const char*);
template std::vector<std::shared_ptr<Citizen>> CitizenDatabase::Query<Citizen>(const char*);
template std::vector<std::shared_ptr<SQLColumns>> CitizenDatabase::Query<SQLColumns>(const char*);

void CitizenDatabase::DeleteCitizen(int citizen_id, int household_id) {
	sqlite3_stmt* delete_citizen;
	sqlite3_prepare_v2(database, "DELETE FROM citizens WHERE id=?", 32, &delete_citizen, nullptr);

	sqlite3_stmt* delete_household;
	sqlite3_prepare_v2(database, "DELETE FROM households INNER JOIN citizens ON citizens.household_id=households.id WHERE household_id=? GROUP BY household_id HAVING COUNT(household_id)=0", 156, &delete_household, nullptr);
	
	sqlite3_bind_int(delete_citizen, 1, citizen_id);

	int out;
	while ((out = sqlite3_step(delete_citizen)) == SQLITE_BUSY) {
		printf("Cannot get a lock on citizens.db");
	}

	if (out != SQLITE_DONE) {
		printf("Encountered unexpected SQL Error trying to delete citizen %i: %i", citizen_id, out);
		return;
	}

	sqlite3_finalize(delete_citizen);
	delete_citizen = nullptr;

	// TODO: Does this delete after deleting the citizen?
	sqlite3_bind_int(delete_household, 1, household_id);

	while((out = sqlite3_step(delete_household)) == SQLITE_BUSY) {
		printf("Cannot get a lock on citizens.db");
	}

	if (out != SQLITE_DONE) {
		printf("Encountered unexpected SQL Error in checking for household %i deletion: %i", out, household_id);
	}
	sqlite3_finalize(delete_household);
	delete_household = nullptr;
}

CitizenDatabase::~CitizenDatabase() {
	sqlite3_close(database);
}