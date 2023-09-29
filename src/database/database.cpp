#include "database.h"
#include <stdexcept>

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
		throw std::runtime_error(std::format("SQL Error: {}", errMessage));
	}
}

CitizenDatabase::~CitizenDatabase() {
	sqlite3_free(database);
	delete database;
}