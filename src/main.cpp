#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include "database/database_window.h"
#include "util/window_management.h"
#include <murder_blog/murder.h>

#ifdef __WIN32
#include <FL/x.H>
#include <windows.h>
#endif

int main(int argc, char **argv) {
	int x, y, w, h;
	Fl::screen_work_area(x, y, w, h);
	Fl_Window* main_window = new Fl_Window(x + w/2, y + h/4, 300, 300, "Spider-880");
	Fl_Box* title = new Fl_Box(20, 20, 260, 100, "Spider-880");
	title->box(FL_DOWN_BOX);
	title->labelsize(36);
	Fl_Box* credits = new Fl_Box(20, 120, 260, 100, "By ambiguousname and stargyaru\nMade with:\nFLTK 1.3.8 (w/ LibPNG support)\nSQLite\nMeson\nPython Faker");
	credits->box(FL_UP_BOX);
	Fl_Button* button = new Fl_Button(100, 240, 100, 50, "Quit");
	button->box(FL_UP_BOX);
	button->callback(WindowManagement::hide_all_windows);

	#ifdef __WIN32
	main_window->icon((char*)LoadIcon(fl_display, MAKEINTRESOURCE(100)));
	#endif
	main_window->end();
	main_window->show(argc, argv);

	main_window->callback(WindowManagement::hide_all_windows);

	WindowManagement::set_main(main_window);

	DatabaseWindow* db = new DatabaseWindow(x + 3 * w/4, y + h/4, 400, 300);
	db->show();
	MurderBlogMurderHTMLWindow* page = new MurderBlogMurderHTMLWindow(x + w/4, y + h/4, 300, 300);
	page->show();

	Fl::run();
	
	return 0;
}