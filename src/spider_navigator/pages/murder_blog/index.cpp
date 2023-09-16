#include "pages.h"
namespace MurderBlogIndexHTMLPage {	
	void onStart() {
		std::cout << "Hello world!";
	}
		
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 300, 300, "My Blog (GEANE: CHANGE TITLE TEXT)");
		Fl_Group *p_6 = new Fl_Group(0, 0, 300, 300);
		Fl_Box *p_6_text_0 = new Fl_Box(0, 0, 300, 300, "Howdy folks");
		p_6->end();
		window->end();
		window->show();
		onStart();
	}
}