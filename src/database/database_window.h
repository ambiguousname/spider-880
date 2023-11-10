#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Button.H>
#include <memory>
#include <string>
#include <vector>
#include "database.h"

typedef std::string (*database_selector)(int tier, int value);
typedef int (*database_choice)();

struct ChoiceOptions {
	std::string name;
	int value;
};

struct ChoiceCategory {
	std::string name;
	std::vector<ChoiceOptions> options;
};


// TODO: Memory storage with  all these structs (and no pointers) is probably really inefficient.
class DatabaseChoice : public Fl_Choice {
	protected:
	int current_category = 0;
	int current_option_value = -1;
	bool categoryLocked = false;
	ChoiceCategory categories[3];
	std::vector<int*> options_val_store;

	database_selector selector;
	std::string label_text;
	
	static void update(Fl_Widget * self, void* option);

	void clearStore();

	public:
	int getCategory() const {return current_category; }
	void selectCategory(int index);
	std::string getSQLString() { if (current_option_value == -1) { return "SELECT * FROM households"; } else { return selector(current_category, current_option_value); } }
	DatabaseChoice(int x, int y, int w, int h, database_selector selector_func, ChoiceCategory choice_categories[3]);
	~DatabaseChoice();
};

class DatabaseWindow : public Fl_Window {
	protected:
	std::unique_ptr<CitizenDatabase> citizen_db;
	
	DatabaseChoice* choices[3];
	int category_tier = 0;

	Fl_Button search_button;
	Fl_Browser database_display;

	std::vector<int> household_ids;
	static void search(Fl_Widget* button, void* self);

	static void selected(Fl_Widget* browser, void* self);
	static void citizenMurdered(Fl_Widget* browser, void* db_window);
	public:
	void updateCategories(int tier);
	int getCategoryTier() const { return category_tier; }
	DatabaseWindow(int x, int y, int w, int h);
	~DatabaseWindow();
};