#include "database.h"

CitizenDatabase::CitizenDatabase(const char* filename) {
	sqlite3_open(filename, &database);
	
}

CitizenDatabase::~CitizenDatabase() {
	sqlite3_free(database);
	delete database;
}