#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <murder_blog/index.h>

int main(int argc, char **argv) {
	MurderBlogIndexHTMLWindow* page = new MurderBlogIndexHTMLWindow(0, 0, 300, 300);
	page->show();

	Fl::run();
	
	return 0;
}