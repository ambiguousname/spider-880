#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/fl_message.H>

#include "database/database_window.h"
#include "util/window_management.h"
#include <murder_blog/murder.h>

#include <util/sound.h>
#include <util/base_sounds.h>

#ifdef __WIN32
#include <FL/x.H>
#include <windows.h>
#endif

#include <fstream>

bool pagesEnabled = false;

void createBlog(Fl_Widget*) {
	if (pagesEnabled) {
		clickSound();
		int x, y, w, h;
		Fl::screen_work_area(x, y, w, h);
		MurderBlogMurderHTMLWindow* page = new MurderBlogMurderHTMLWindow(x + w/4, y + h/4, 300, 300);
		page->show();
	} else {
		errorSound();
		fl_alert("Browsing is not yet enabled.\nYou must select a name.");
	}
}

void overrideCitizenSelection(Fl_Widget*) {
	fl_alert("Guessing won't get you anywhere.\nLucky you have an internet connection.");
	pagesEnabled = true;
	createBlog(nullptr);
	FILE* f = fopen("savefile.txt", "w");
	fputs("I'll give you one more password: abababab.", f);
	fclose(f);
}

#include "win_screen.h"
int main(int argc, char **argv) {
	int x, y, w, h;
	Fl::screen_work_area(x, y, w, h);
	Fl_Window* main_window = new Fl_Window(x + w/2, y + h/4, 300, 350, "Spider-880");
	Fl_Box* title = new Fl_Box(20, 20, 260, 100, "Spider-880");
	title->box(FL_DOWN_BOX);
	title->labelsize(36);
	Fl_Box* credits = new Fl_Box(20, 120, 260, 120, "By ambiguousname\n(with thanks to stargyaru)\nMade with:\nFLTK 1.3.8 (w/ LibPNG support),\nminiaudio, SQLite,\nMeson, Python Faker");
	credits->box(FL_UP_BOX);
	Fl_Button* browser = new Fl_Button(80, 240, 120, 50, "Launch Browser");
	browser->box(FL_UP_BOX);
	browser->callback(createBlog);
	Fl_Button* button = new Fl_Button(80, 290, 120, 50, "Quit");
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
		// To avoid playing the sound.
		int x, y, w, h;
		Fl::screen_work_area(x, y, w, h);
		MurderBlogMurderHTMLWindow* page = new MurderBlogMurderHTMLWindow(x + w/4, y + h/4, 300, 300);
		page->show();
	} else {
		db->citizenSelectedOverride(overrideCitizenSelection);
	}

	// TODO: Audio playback for a few sounds (looping backgrounds too)
	// TODO: OpenGL scares
	SoundManager::Initialize();

	SoundManager::Sound startup;
	SoundManager::Load("./assets/startup.wav", startup);
	startup.play();

	Fl::run();

	SoundManager::Sound close;
	SoundManager::Load("./assets/close.wav", close);
	close.play();
	close.awaitPlay();
	
	SoundManager::Uninitialize();
	return 0;
}