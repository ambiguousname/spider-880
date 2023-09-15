#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "util/image_box.h"
#include <filesystem>
#include <FL/Fl_Shared_Image.H>

int main(int argc, char **argv) {
	fl_register_images();
	Fl_Window *window = new Fl_Window(340,480, "Test");
	ImageBox *box = new ImageBox("./assets/test.png", 20,40,300,400);
	/* // This also works:
	for (int i = 0; i < 10; i++) {
		ImageBox *box = new ImageBox("./assets/test.png", 20,40 * i,100,100);
	}*/
	// box->box(FL_UP_BOX);

	// box->image(temp);

	window->end();
	window->show(argc, argv);

	// Fl::add_timeout(0.01, draw_img);
	return Fl::run();
}