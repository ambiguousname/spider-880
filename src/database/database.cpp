#include "database.h"
#include <stdio.h>
#include <string>

column_key* SQLColumns::getValuePtr(std::string key) {
	if (key == "id") {
		return &id;
	}
	return nullptr;
}

void SQLColumns::update(char* key, char* value) {
	column_key value_key = std::make_unique<std::string>(value);
	std::string key_string = std::string(key);
	column_key* value_ptr = getValuePtr(key_string);
	value_key.release();
	if (value_ptr == nullptr) {
		fprintf(stderr, "SQL unidentified key %s for %s", key, typeid(this).name());
	} else {
		value_ptr->swap(value_key);
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
	sqlite3_open(filename, &database);
}

template<class T>
static int query_callback(db_callback<T> callback, int argc, char** argv, char** azColName) {
	T columns;
	for (int i = 0; i < argc; i++) {
		columns.update(azColName[i], argv[i]);
	}
	callback(columns);
	return 0;
}

template<class T>
void CitizenDatabase::query(const char *query_text, db_callback<T> callback) {
	char *errMessage = 0;
	int code = sqlite3_exec(database, query_text, query_callback, callback, &errMessage);
	if (code != SQLITE_OK) {
		fprintf(stderr, "SQL query error: %s", errMessage);
		sqlite3_free(errMessage);
	}
}

CitizenDatabase::~CitizenDatabase() {
	sqlite3_close(database);
}