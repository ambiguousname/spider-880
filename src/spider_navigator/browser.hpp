#pragma once
#include <FL/Fl_Window.H>
#include <string>
#include "page.hpp"

void initializeBrowser();
void uninitializeBrowser();

void newWindow(std::string site, std::string filename, int x, int y, int w, int h);

class BrowserWindow : public Fl_Window {
	void drawChildren();
	
	Fl_Menu_Bar menu_bar;

	HTMLPage* page;
	Fl_Scroll* scrollbar;

	std::string title;

	public:
	BrowserWindow(std::string filepath, int x, int y, int w, int h);

};