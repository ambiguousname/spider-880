#include "database_window.h"
#include "util/window_management.h"
#include <FL/Fl_Box.H>
#include <FL/fl_message.H>
#include "../win_screen.h"

DatabaseChoice::DatabaseChoice(int x, int y, int w, int h, database_selector selector_func, ChoiceCategory choice_categories[3]) : Fl_Choice(x, y, w, h), selector(selector_func) {

	for (int i = 0; i < 3; i++) {
		categories[i] = choice_categories[i];
	}
	
	label(label_text.c_str());
}

DatabaseChoice::~DatabaseChoice() {
	clearStore();
}

void DatabaseChoice::clearStore() {
	for (int* val : options_val_store) {
		delete val;
	}
	options_val_store.clear();
}

void DatabaseChoice::selectCategory(int index) {
	if (!categoryLocked) {
		current_category = index;
		clear();
		clearStore();
		label_text = std::string("Tier ") + std::to_string(index) + " " + categories[index].name + ":";
		label(label_text.c_str());
		static int negative = -1;
		add("No Selection", 0, update, &negative);
		for (ChoiceOptions option : categories[index].options) {
			int* val = new int(option.value);
			options_val_store.push_back(val);
			add(option.name.c_str(), 0, update, val);
		}
		
		value(0);
	}
}

void DatabaseChoice::update(Fl_Widget* s, void* option) {
	int value = (*static_cast<int*>(option));
	
	DatabaseChoice* self = static_cast<DatabaseChoice*>(s);
	if (value != self->current_option_value){
		self->current_option_value = value;
		DatabaseWindow* parent = static_cast<DatabaseWindow*>(self->parent());
		int tier = parent->getCategoryTier();
		if (value == -1) {
			self->categoryLocked = false;
			tier -= 1;
		} else if (!self->categoryLocked) {
			self->categoryLocked = true;
			tier += 1;
		}
		parent->updateCategories(tier);
	}
}


#pragma region SQL_Definitions

// TODO: Area/District/Subdistrict names.
std::vector<ChoiceOptions> area_options {{"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}};

// TODO: Make these binding instead.
std::string selectArea(int tier, int value) {
	std::string base_selector = "SELECT * FROM households WHERE SUBSTRING(households.zip, " + std::to_string(tier + 1) + ", 1) = '" + std::to_string(value) + "'";
	if (value == 0) {
		base_selector += " OR LENGTH(households.zip) < " + std::to_string(tier + 1);
	}
	return base_selector;
}

// Integer formating: 1 byte for HIGH (1-255), 1 byte for LOW (1-255), so the byte formatting is: HIGHLOW on an integer.

ChoiceCategory income_percent {
	"Income %",
	{
		{"Top 10%", 0b1111111101011010}, // > 0.9
		{"10%-20%", 0b0101101001010000},
		{"20%-30%", 0b0101000001000110},
		{"30%-40%", 0b0100011000111100},
		{"40%-50%", 0b0011110000110010},
		{"50%-60%", 0b0011001000101000},
		{"60%-70%", 0b0010100000011110},
		{"70%-80%", 0b0001111000010100},
		{"80%-90%", 0b0001010000001010},
		{"Bottom 90%", 0b0000101000000000}, // < 0.1
	}
};

ChoiceCategory income_range {
	"Income/mo",
	{
		{"<$5k", 0b0000010100000000},
		{"$5k-$10k", 0b0000101000000101},
		{"$10k-$20k",0b0001010000001010},
		{">$20k", 0b1111111100010100}
	}
};

ChoiceCategory income_range_fine {
	"Income/mo",
	{
		{"<$5k", 0b0000010100000000},
		{"$5k-$8k", 0b0000100000000101},
		{"$8k-$10k", 0b0000101000001000},
		{"$10k-$15k", 0b0000111100001010},
		{"$15k-$20k",0b0001010000001111},
		{">$20k", 0b1111111100010100}
	}
};

std::string selectIncome(int tier, int value) {
	int high = (value >> 8) & 0b11111111;
	int low = value & 0b11111111;
	if (tier >= 1) {
		return "SELECT households.* FROM households JOIN citizens ON households.id = citizens.household_id WHERE citizens.income > " + std::to_string(low * 1000) + " AND citizens.income < " + std::to_string(high * 1000) + " GROUP BY household_id";
	}
	if (high >= 255) {
		high = 999;
	}
	// TODO: This doesn't work for the 100% highest earner.
	return "SELECT households.* FROM (SELECT household_id, PERCENT_RANK() OVER(ORDER BY income) AS percent FROM citizens JOIN households ON households.id = citizens.household_id) rankings JOIN households ON households.id = rankings.household_id WHERE rankings.percent >= 0." + std::to_string(low) + " AND rankings.percent <= 0." + std::to_string(high) + " GROUP BY household_id";
}

ChoiceCategory family_married {
	"Family",
	{
		{"Lives In A Family", 0},
		{"Does Not Live In A Family", 1}
	}
};

ChoiceCategory family_spouse {
	"Living",
	{
		{"Married, Living With Family", 0},
		{"Not Married, Living With Family", 1},
		{"Not Married, Living Alone", 2},
		{"Not Married, Not Living Alone", 3}
	}
};

ChoiceCategory family_count {
	"Size",
	{
		{"1", 1},
		{"2", 2},
		{"3", 3},
		{"4", 4},
		{"5", 5}
	}
};

std::string selectFamily(int tier, int value) {
	if (tier == 2) {
		return "SELECT households.* FROM households JOIN citizens ON households.id = citizens.household_id GROUP BY household_id HAVING count(household_id) > " + std::to_string(value);
	}
	if (tier == 0) {
		// EITHER: Married w/ Family or Not Married w/ Family
		int value_zero = 0;
		int value_one = 1;
		// OR Not Married, Living Alone, OR Not Married, Not Living Alone
		if (value == 1) {
			value_zero = 2;
			value_one = 3;
		}
		return "SELECT * FROM households WHERE family_status = " + std::to_string(value_zero) + " OR family_status = " + std::to_string(value_one);
	}
	return "SELECT * FROM households WHERE family_status = " + std::to_string(value);
}

ChoiceCategory area_arr[3] = {{"Area", area_options}, {"District", area_options}, {"Subdistrict", area_options}};

ChoiceCategory income_arr[3] = {income_percent, income_range, income_range_fine};

ChoiceCategory family_arr[3] = {family_married, family_spouse, family_count};

#pragma endregion SQL_Definitions

const int database_widths[] = {40, 150, 0};
DatabaseWindow::DatabaseWindow(int x, int y, int w, int h) : Fl_Window(x, y, w, h, "Citizen Database"), citizen_db(new CitizenDatabase("citizens.db")), choices{new DatabaseChoice(120, 20, w - 120, 20, selectArea, area_arr), new DatabaseChoice(120, 40, w - 120, 20, selectIncome, income_arr), new DatabaseChoice(120, 60, w - 120, 20, selectFamily, family_arr)}, search_button(0, 80, w, 20, "Search"), database_display(0, 100, w, h - 100) {
	Fl_Box* b = new Fl_Box(0, 0, w, 20, "Who was murdered? Select them here.");
	database_display.column_widths(database_widths);
	database_display.type(FL_HOLD_BROWSER);

	callback(WindowManagement::essential_hide);
	updateCategories(category_tier);
	search_button.callback(search, this);
	database_display.callback(selected, this);
	resizable(this);
	end();
}

DatabaseWindow::~DatabaseWindow() {
	for (DatabaseChoice* i : choices) {
		delete i;
	}
}

void DatabaseWindow::updateCategories(int tier) {
	category_tier = tier;
	for (DatabaseChoice* i : choices) {
		i->selectCategory(category_tier);
	}
	redraw();
}

void DatabaseWindow::search(Fl_Widget*, void* s) {
	DatabaseWindow* self = static_cast<DatabaseWindow*>(s);
	std::vector<std::string> search_text;

	for (auto choice : self->choices) {
		std::string sql = choice->getSQLString();
		if (sql != "") {
			search_text.push_back(sql);
		}
	}

	std::string full_search_text = "";
	for (long long unsigned int i = 0; i < search_text.size(); i++) {
		full_search_text += search_text[i];
		if (i < search_text.size() - 1) {
			full_search_text += " INTERSECT ";
		}
	}
	std::vector<std::shared_ptr<Household>> households = self->citizen_db->Query<Household>(full_search_text.c_str());

	self->household_ids.clear();
	self->database_display.clear();
	self->database_display.add("ID\tFAMILY_STATUS\tZIP");

	for (auto household : households) {
		char buf[50];
		const char* family_status = 0;
		std::string status = *household->family_status;
		if (status == "0") {
			family_status = "Married w/ Family";
		} else if (status == "1") {
			family_status = "Unmarried W/ Family";
		} else if (status == "2") {
			family_status = "Living Alone";
		} else if (status == "3") {
			family_status = "Not Living Alone";
		}

		std::string id = *household->id;
		self->household_ids.push_back(std::stoi(id));
		std::string zip = *household->zip;

		sprintf(buf, "%s\t%s\t%s", id.c_str(), family_status, zip.c_str());
		self->database_display.add(buf);
		self->database_display.redraw();
	}
}

void DatabaseWindow::citizenMurdered(Fl_Widget* browser, void* db_window) {
	Fl_Browser* self = static_cast<Fl_Browser*>(browser);
	if (self->value() <= 1) {
		return;
	}

	Citizen citizen = Citizen(self->text(self->value()));
	int choice = fl_choice("Was %s %s murdered?", "No", "Yes", nullptr, citizen.first_name->c_str(), citizen.last_name->c_str());
	if (choice == 1) {
		// Assuming database hasn't changed.
		// TODO: Update based on how python generates the IDs.
		if (std::stoi(citizen.id->c_str()) == 70) {
			new WinScreen();
		} else {
			static_cast<DatabaseWindow*>(db_window)->citizen_db->DeleteCitizen(std::stoi(citizen.id->c_str()), std::stoi(citizen.household_id->c_str()));
			fl_alert("Soul no longer found. Your guess must have been incorrect.");

			self->remove(self->value());
			self->redraw();
		}
	}
}

void DatabaseWindow::citizenOverride(Fl_Widget* widget, void* parent) {
	DatabaseWindow* self = static_cast<DatabaseWindow*>(parent);
	self->citizen_selected_override(widget);
	self->citizen_selected_override = nullptr;
	widget->top_window()->hide();
}

const int citizen_widths[] = {40, 40, 70, 70, 70, 50, 0};
void DatabaseWindow::selected(Fl_Widget* widget, void* parent) {
	DatabaseWindow* self = static_cast<DatabaseWindow*>(parent);
	Fl_Browser* browser = static_cast<Fl_Browser*>(widget);
	int index = browser->value() - 2;
	if (index >= 0) {
		int household_id = self->household_ids[index];
		char buf[50];
		sprintf(buf, "SELECT * FROM citizens WHERE household_id=%i", household_id);
		std::vector<std::shared_ptr<Citizen>> citizens = self->citizen_db->Query<Citizen>(buf);
		Fl_Window* household_window = new Fl_Window(self->x() + 10, self->y() + 10, self->w(), self->h(), buf);
		Fl_Browser* citizen_browser = new Fl_Browser(0, 0, household_window->w(), household_window->h());
		if (self->citizen_selected_override != nullptr) {
			citizen_browser->callback(citizenOverride, self);
		} else {
			citizen_browser->callback(citizenMurdered, self);
		}

		citizen_browser->column_widths(citizen_widths);
		citizen_browser->type(FL_HOLD_BROWSER);
		citizen_browser->add("ID\tAGE\tF.NAME\tL.NAME\tINCOME\tHOUSE\tSPOUSE");
		for (auto citizen: citizens) {
			char citizen_text[200];
			citizen->toString(citizen_text);
			
			citizen_browser->add(citizen_text);
		}
		household_window->resizable(citizen_browser);

		household_window->end();
		household_window->show();
	}
}