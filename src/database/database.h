#pragma once
#include <sqlite3.h>

class SQLColumns {
	protected:
	virtual void update(char* key, char* value) = 0;
};

class Citizen : SQLColumns {
	protected:
	void update(char* key, char* value) override;
};


template<typename T>
typedef void (*db_callback)(T* columns);

class CitizenDatabase {
	sqlite3 *database;
	void query(const char* query_text, db_callback callback);
	public:
	CitizenDatabase(const char* filename);
	void QueryCitizen();
	~CitizenDatabase();
};