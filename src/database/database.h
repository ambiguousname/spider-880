#pragma once
#include <sqlite3.h>

class CitizenDatabase {
	sqlite3 *database;
	CitizenDatabase(const char* filename);
	~CitizenDatabase();
};