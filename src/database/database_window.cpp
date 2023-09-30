#include "database_window.h"
#include "util/hide_all_windows.h"

DatabaseChoice::DatabaseChoice(int x, int y, int w, int h, database_selector first, database_selector second, database_selector third) : choice(x, y, w, h), selectors({first, second, third}) {
	
}

// TODO: Combine with INTERSECT statements.
std::string selectArea(int tier, int value) {
	std::string base_selector = "SELECT * FROM households WHERE SUBSTRING(households.zip, " + std::to_string(tier + 1) + ", 1) = '" + std::to_string(value) + "'";
	if (value == 0) {
		base_selector += " OR LENGTH(households.zip) < " + std::to_string(tier + 1);
	}
	base_selector += ";";
	return base_selector;
}

std::string selectIncome(int tier, int value) {
	if (tier == 0) {
		return "SELECT households.* FROM households JOIN citizens ON households.id = citizens.household_id WHERE citizens.income >" + std::to_string(value) + " GROUP BY household_id;";
	}
	return "SELECT households.* FROM households JOIN citizens ON households.id = citizens.household_id WHERE citizens.income > X GROUP BY household_id, or for percentile rankings: SELECT households.* FROM (SELECT household_id, PERCENT_RANK() OVER(ORDER BY income) AS Percent FROM citizens JOIN households ON households.id = citizens.household_id) rankings JOIN households ON households.id = rankings.household_id WHERE rankings.Percent > " + std::to_string(value) + " GROUP BY household_id;";
}

std::string selectFamily(int tier, int value) {
	if (tier == 2) {
		return "SELECT households.* FROM households JOIN citizens ON households.id = citizens.household_id GROUP BY household_id HAVING count(household_id) > " + std::to_string(value) + ";";
	}
	return "SELECT * FROM households WHERE family_status = " + std::to_string(value) + ";";
}

DatabaseWindow::DatabaseWindow(int x, int y, int w, int h) : Fl_Window(x, y, w, h, "Citizen Database"), citizen_db(), area(0, 0, 100, 20), income(0, 20, 100, 20), family(0, 40, 100, 20), database_display(0, 80, w, h - 80) {
	resizable(this);
	end();
}

void DatabaseWindow::hide() {
	Fl_Window::hide();
	hide_all_windows();
}