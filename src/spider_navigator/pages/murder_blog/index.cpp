#include "pages.h"
namespace MurderBlogIndexHTMLPage {	
	void onStart() {
		std::cout << "Hello world!";
	}
		
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 300, 300, "My Blog (GEANE: CHANGE TITLE TEXT)");
		ImageBox *img_6 = new ImageBox("./assets/test.png", 0, 0, 300, 300);
		Fl_Group *p_7 = new Fl_Group(0, 0, 300, 300);
		Fl_Box *p_7_text_0 = new Fl_Box(0, 0, 300, 300, "Howdy folks! Welcome to the murder show.");
		p_7->end();
		window->end();
		window->show();
		onStart();
	}
}