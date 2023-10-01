#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "database/database_window.h"
#include <murder_blog/index.h>

int main(int argc, char **argv) {
	int x, y, w, h;
	Fl::screen_work_area(x, y, w, h);
	DatabaseWindow* db = new DatabaseWindow(x + w/2, y + h/4, 300, 300);
	db->show();
	MurderBlogIndexHTMLWindow* page = new MurderBlogIndexHTMLWindow(x + w/4, y + h/4, 300, 300);
	page->show();

	Fl::run();
	
	return 0;
}