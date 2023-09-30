#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Table.H>
#include <memory>
#include <string>
#include "database.h"

typedef std::string (*database_selector)(int tier, int value);

struct DatabaseChoice {
	Fl_Choice choice;
	database_selector selectors[3];
	DatabaseChoice(int x, int y, int w, int h, database_selector first, database_selector second, database_selector third);
};

class DatabaseWindow : public Fl_Window {
	std::unique_ptr<CitizenDatabase> citizen_db;
	
	// For combining: JOIN households ON households.id = citizens.household_id
	DatabaseChoice area; // SELECT * FROM households WHERE SUBSTRING(households.zip, Y, 1) = 'X'. If X is 0, instead use: SELECT * FROM households WHERE SUBSTRING(households.zip, 1, 1) = '0' OR LENGTH(households.zip) < 3, either that or: SELECT * FROM households WHERE SUBSTRING(households.zip, 2, 1) = '0' OR LENGTH(households.zip) < 3
	DatabaseChoice income; // SELECT households.* FROM households JOIN citizens ON households.id = citizens.household_id WHERE citizens.income > X GROUP BY household_id, or for percentile rankings: SELECT households.* FROM (SELECT household_id, PERCENT_RANK() OVER(ORDER BY income) AS Percent FROM citizens JOIN households ON households.id = citizens.household_id) rankings JOIN households ON households.id = rankings.household_id WHERE rankings.Percent > 0.5;
	DatabaseChoice family; // SELECT * FROM households WHERE family_status = X, SELECT households.* FROM households JOIN citizens ON households.id = citizens.household_id GROUP BY household_id HAVING count(household_id) > X

	Fl_Table database_display;

	protected:
	void hide();
	public:
	DatabaseWindow(int x, int y, int w, int h);
};