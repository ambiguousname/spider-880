#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include "database/database_window.h"
#include "util/window_management.h"
#include <murder_blog/index.h>

int main(int argc, char **argv) {
	int x, y, w, h;
	Fl::screen_work_area(x, y, w, h);
	Fl_Window* main_window = new Fl_Window(x + w/2, y + h/4, 300, 300);
	Fl_Box* credits = new Fl_Box(20, 20, 260, 100, "Spider-880\nBy ambiguousname and stargyaru\nMade with: FLTK 1.3.8");
	credits->box(FL_UP_BOX);
	Fl_Button* button = new Fl_Button(100, 140, 100, 50, "Quit");
	button->box(FL_UP_BOX);
	button->callback(WindowManagement::hide_all_windows);
	main_window->end();
	main_window->show();

	WindowManagement::set_main(main_window);

	DatabaseWindow* db = new DatabaseWindow(x + 3 * w/4, y + h/4, 300, 300);
	db->show();
	MurderBlogIndexHTMLWindow* page = new MurderBlogIndexHTMLWindow(x + w/4, y + h/4, 300, 300);
	page->show();

	Fl::run();
	
	return 0;
}