#pragma once
#include <sqlite3.h>
#include <memory>
#include <concepts>
// TODO: I wonder if there's some kind of C++ variant that allows for macros before compiling?
// I think having a language that pre-compiles into C++ would be suuuuper useful for readability and editing.
// Maybe a gcc plugin or something? https://thinkingeek.com/2015/08/16/a-simple-plugin-for-gcc-part-1/
// This completely sucks otherwise. I certainly wish C++ had a more robust macro system (like Rust. Le sigh...)

typedef std::unique_ptr<std::string> column_key; 

class SQLColumns {
	protected:
	// Return a pointer to the smart pointer to set its value.
	virtual column_key* getValuePtr(std::string key);
	void update(char* key, char* value);
	column_key id;
};

class Citizen : SQLColumns {
	protected:
	column_key* getValuePtr(std::string key) override;
	column_key age;
	column_key first_name;
	column_key last_name;
	column_key income;
	column_key household_id;
	column_key spouse_id;
};

class Household : SQLColumns {
	protected:
	column_key* getValuePtr(std::string key) override;
	column_key family_status;
	column_key zip;
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