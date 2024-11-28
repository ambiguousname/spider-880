#pragma once
#include <FL/Fl_Window.H>
#include <string>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Menu_Bar.H>

namespace Browser {
	void Initialize();
	void Uninitialize();

	void NewWindow(std::string site, std::string filename, int x, int y, int w, int h);

	void VisitPage(std::string filepath);
	bool VisitedPage(std::string filepath);
}

class Body;

class BrowserWindow : public Fl_Window {
	Fl_Menu_Bar menu_bar;

	Body* body;
	Fl_Scroll* scrollbar;

	std::string title;

	void evaluateHead(htmlNodePtr head);
	int evaluateHTML(std::string filepath, int x, int y, int w, int h);

	public:
	BrowserWindow(std::string filepath, int x, int y, int w, int h);
	void draw();
};