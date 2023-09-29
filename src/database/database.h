#pragma once
#include <sqlite3.h>
#include <concepts>

class SQLColumns {
	protected:
	virtual void update(char* key, char* value) = 0;
};

class Citizen : SQLColumns {
	protected:
	void update(char* key, char* value) override;
};


template<class ColType> requires std::derived_from<ColType, SQLColumns>
using db_callback = void (*)(ColType* columns);

class CitizenDatabase {
	sqlite3 *database;
	template<class T>
	void query(const char* query_text, db_callback<T> callback);
	public:
	CitizenDatabase(const char* filename);
	void QueryCitizen();
	~CitizenDatabase();
};