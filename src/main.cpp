#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/fl_message.H>

#include "database/database_window.h"
#include "util/window_management.h"
#include <murder_blog/murder.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#ifdef __WIN32
#include <FL/x.H>
#include <windows.h>
#endif

#include <fstream>

bool pagesEnabled = false;

void createBlog(Fl_Widget*) {
	if (pagesEnabled) {
		int x, y, w, h;
		Fl::screen_work_area(x, y, w, h);
		MurderBlogMurderHTMLWindow* page = new MurderBlogMurderHTMLWindow(x + w/4, y + h/4, 300, 300);
		page->show();
	} else {
		fl_alert("Browsing is not yet enabled.\nYou must select a name.");
	}
}

void overrideCitizenSelection(Fl_Widget*) {
	fl_alert("Guessing won't get you anywhere.\nLucky you have a connection.");
	pagesEnabled = true;
	createBlog(nullptr);
	FILE* f = fopen("savefile.txt", "w");
	fputs("I'll give you one more password: abababab.", f);
	fclose(f);
}

#include "win_screen.h"
int main(int argc, char **argv) {
	new WinScreen();
	int x, y, w, h;
	Fl::screen_work_area(x, y, w, h);
	Fl_Window* main_window = new Fl_Window(x + w/2, y + h/4, 300, 350, "Spider-880");
	Fl_Box* title = new Fl_Box(20, 20, 260, 100, "Spider-880");
	title->box(FL_DOWN_BOX);
	title->labelsize(36);
	Fl_Box* credits = new Fl_Box(20, 120, 260, 120, "By ambiguousname and stargyaru\nMade with:\nFLTK 1.3.8 (w/ LibPNG support)\nminiaudio\nSQLite\nMeson\nPython Faker");
	credits->box(FL_UP_BOX);
	Fl_Button* browser = new Fl_Button(100, 240, 100, 50, "Launch Browser");
	browser->box(FL_UP_BOX);
	browser->callback(createBlog);
	Fl_Button* button = new Fl_Button(100, 290, 100, 50, "Quit");
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

	if (FILE* file = fopen("savefile.txt", "r")) {
		fclose(file);
		pagesEnabled = true;
	}

	if (pagesEnabled){
		createBlog(nullptr);
	} else {
		db->citizenSelectedOverride(overrideCitizenSelection);
	}

	// TODO: Audio playback for a few sounds (looping backgrounds too)
	// TODO: OpenGL scares
	// ma_result result;
	// ma_engine engine;
	
	// result = ma_engine_init(NULL, &engine);
	// if (result != MA_SUCCESS) {
	// 	std::cout << "Could not initialize audio engine." << std::endl;
	// 	return result;
	// }

	// ma_engine_play_sound(&engine, "./assets/zombiegenericshort11.wav", NULL);

	Fl::run();
	
    // ma_engine_uninit(&engine);
	return 0;
}