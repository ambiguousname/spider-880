#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "util/image_box.h"

int main(int argc, char **argv) {
	Fl_Window *window = new Fl_Window(340,180, "Test");
	ImageBox *box = new ImageBox("assets/test.png", 20,40,300,100);
	// box->box(FL_UP_BOX);

	// box->image(temp);

	window->end();
	window->show(argc, argv);

	// Fl::add_timeout(0.01, draw_img);
	return Fl::run();
}