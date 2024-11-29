#pragma once
#include <sqlite3.h>
#include <memory>
#include <vector>
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
	public:
	void update(char* key, char* value);
	column_key id;

	virtual ~SQLColumns() {
		id.release();
	}
};

class Citizen : public SQLColumns {
	protected:
	column_key* getValuePtr(std::string key) override;
	public:
	column_key age;
	column_key first_name;
	column_key last_name;
	column_key income;
	column_key household_id;
	column_key spouse_id;

	Citizen() {}
	
	Citizen(std::string s) {
		std::string buf = "";
		int idx = 0;
		for (auto c: s) {
			if (c == '\t' || c == '\0') {
				column_key* to_set;
				switch (idx) {
					case 0:
						to_set = &id;
						break;
					case 1:
						to_set = &age;
						break;
					case 2:
						to_set = &first_name;
						break;
					case 3:
						to_set = &last_name;
						break;
					case 4:
						to_set = &income;
						break;
					case 5:
						to_set = &household_id;
						break;
					case 6:
						to_set = &spouse_id;
						break;
					default:
						to_set = nullptr;
						break;
				}
				*to_set = column_key(std::make_unique<std::string>(buf));
				buf = "";
				idx++;
			} else {
				buf += c;
			}
		}
	}
	
	void toString(char out[]) const {
		sprintf(out, "%s\t%s\t%s\t%s\t%s\t%s\t%s", id->c_str(), age->c_str(), first_name->c_str(), last_name->c_str(), income->c_str(), household_id->c_str(), spouse_id->c_str());
	}

	~Citizen() {
		age.release();
		first_name.release();
		last_name.release();
		income.release();
		household_id.release();
		spouse_id.release();
	}
};

class Household : public SQLColumns {
	protected:
	column_key* getValuePtr(std::string key) override;
	public:
	column_key family_status;
	column_key zip;
};

class CitizenDatabase {
	sqlite3 *database;
	public:
	CitizenDatabase(const char* filename);
	template<class T> requires std::derived_from<T, SQLColumns>
	std::vector<std::shared_ptr<T>> Query(const char* query);
	void DeleteCitizen(int citizen_id);
	~CitizenDatabase();
};