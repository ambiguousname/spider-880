#pragma once
#include <FL/Fl_Window.H>
#include <string>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Menu_Bar.H>
#include "tags.hpp"

void initializeBrowser();
void uninitializeBrowser();

void newWindow(std::string site, std::string filename, int x, int y, int w, int h);

class BrowserWindow : public Fl_Window {
	Fl_Menu_Bar menu_bar;

	Body* body;
	Fl_Scroll* scrollbar;

	std::string title;

	void evaluateHead(xmlpp::Element* head);

	public:
	BrowserWindow(std::string filepath, int x, int y, int w, int h);
	void draw();
};