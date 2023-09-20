#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "util/image_box.h"

#include <iostream>
int main(int argc, char **argv) {
	// MurderBlogIndexHTMLWindow* page = new MurderBlogIndexHTMLWindow(0, 0, 300, 300);
	// page->show();
	Fl_Window* w = new Fl_Window(0, 0, 300, 300, "test");
	ImageBox* box = new ImageBox("./assets/palette.png", 0, 0, 300, 300);
	w->end();
	w->show();

	Fl::run();
	
	return 0;
}