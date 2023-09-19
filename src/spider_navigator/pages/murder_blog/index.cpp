#include "pages.h"
namespace MurderBlogIndexHTMLPage {	
	void onStart() {
		std::cout << "Hello world!";
	}
		
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 300, 300, "5");
		// fl_draw("Test", 0, 0);
		window->end();
		window->resizable(*window);
		window->show();
		onStart();
		Fl::run();
	}
}