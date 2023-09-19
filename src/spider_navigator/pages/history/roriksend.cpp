#include "pages.h"
namespace HistoryRoriksendHTMLPage {
	void onStart() {}
	void draw() {
		Fl_Window *window = new Fl_Window(0, 0, 0, 0, "2");
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		fl_draw("Test", 0, 0);
		window->end();
		window->resizable(*window);
		window->show();
		onStart();
		Fl::run();
	}
}