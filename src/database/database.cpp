#include "database.h"
#include <stdexcept>
#include <format>

CitizenDatabase::CitizenDatabase(const char* filename) {
	sqlite3_open(filename, &database);
}

static int query_callback(db_callback callback, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		columns.cols[azColName[i]] = argv[i];
	}
	callback();
	return 0;
}

void CitizenDatabase::query(const char *query_text, db_callback callback) {
	char *errMessage = 0;
	int code = sqlite3_exec(database, query_text, query_callback, &columns, &errMessage);
	if (errMessage > 0) {
		throw std::runtime_error(std::format("SQL Error: {}", errMessage));
	}
}

CitizenDatabase::~CitizenDatabase() {
	sqlite3_free(database);
	delete database;
}