#include "database.h"
#include <stdio.h>
#include <string>
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

CitizenDatabase::~CitizenDatabase() {
	sqlite3_close(database);
}