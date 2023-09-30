#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "database/database_window.h"
#include <murder_blog/index.h>

int main(int argc, char **argv) {
	DatabaseWindow* db = new DatabaseWindow(100, 100, 300, 300);
	db->show();
	MurderBlogIndexHTMLWindow* page = new MurderBlogIndexHTMLWindow(0, 0, 300, 300);
	page->show();

	Fl::run();
	
	return 0;
}