#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "util/image_window.h"

void draw_img(void*) {
	static Fl_PNG_Image *img = new Fl_PNG_Image("./assets/test.png");
	static Fl_Image* temp = img->copy(300 * img->w()/img->h(), 100 * img->w()/img->h());

	static int y = 0;  
	static int x = 0;
	static const char *buf = temp->data()[0];

	for (int i = 0; i < rand(); i++){
		if (x >= temp->w()) {
			y += 1;
			x = 0;
		}
		if (y >= temp->h()) {
			y = 0;
			x = 0;
			return;
		}
		long index = (y * temp->w() * temp->d()) + (x * temp->d());

		unsigned char r = *(buf + index);
		unsigned char g = *(buf + index + 1);
		unsigned char b = *(buf + index + 2);

		fl_color(r, g, b);
		fl_point(x, y);
		x += 1;
	}
	Fl::repeat_timeout(0.01, draw_img);
}

int main(int argc, char **argv) {
	ImageWindow *window = new ImageWindow("t", 340,180, "Test");
	Fl_Box *box = new Fl_Box(20,40,300,100);

	// box->image(temp);

	window->end();
	window->show(argc, argv);

	// Fl::add_timeout(0.01, draw_img);
	return Fl::run();
}