#pragma once
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Table.H>
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

	database_selector selector;
	std::string label_text;
	
	static void update(Fl_Widget * self, void* option);
	public:
	int getCategory() const {return current_category; }
	void selectCategory(int index);
	DatabaseChoice(int x, int y, int w, int h, database_selector selector_func, ChoiceCategory choice_categories[3]);
};

class DatabaseWindow : public Fl_Window {
	std::unique_ptr<CitizenDatabase> citizen_db;
	
	DatabaseChoice* choices[3];
	int category_tier = 0;

	Fl_Button search_button;
	Fl_Table database_display;
	public:
	void updateCategories(int tier);
	int getCategoryTier() const { return category_tier; }
	DatabaseWindow(int x, int y, int w, int h);
	~DatabaseWindow();
};