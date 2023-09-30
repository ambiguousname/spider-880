#pragma once
#include <FL/Fl_Window.H>
#include <memory>
#include <FL/Fl_Light_Button.H>
#include "database.h"

class DatabaseWindow : public Fl_Window {
	std::unique_ptr<CitizenDatabase> citizen_db;
	
	Fl_Light_Button area;
	Fl_Light_Button income;
	Fl_Light_Button family;
	public:
	DatabaseWindow(int x, int y, int w, int h);
};