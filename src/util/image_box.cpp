#include "image_box.h"
#include "color.h"
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl.H>

ImageBox::ImageBox(const char* image_loc, int x, int y, int w, int h) : Fl_Widget(x, y, w, h) {
	Fl_PNG_Image* tmp = new Fl_PNG_Image(image_loc); 
	image = tmp->copy(w, h);
	image_buffer = image->data()[0];
	delete tmp;
}

ImageBox::~ImageBox() {
	delete image;
}

void ImageBox::drawProgress(int speed) {
	for (int i = 0; i < speed; i++) {
		if (draw_cursor_x >= image->w()) {
			draw_cursor_y += 1;
			draw_cursor_x = 0;
		}
		if (draw_cursor_y >= image->h()) {
			draw_cursor_x = 0;
			draw_cursor_y = 0;
			rendered = true;
			return;
		}
		long index = (draw_cursor_y * image->w() * image->d()) + (draw_cursor_x * image->d());

		unsigned char r = *(image_buffer + index);
		unsigned char g = *(image_buffer + index + 1);
		unsigned char b = *(image_buffer + index + 2);

		fl_color(rgb_to_palette(r, g, b));
		fl_point(draw_cursor_x + x(), draw_cursor_y + y());
		draw_cursor_x += 1;
	}
}

void ImageBox::draw() {
	fl_draw_box(FL_UP_BOX, x(), y(), w(), h(), FL_BACKGROUND_COLOR);
	// TODO: More efficient code for damaged or fully drawn ("cached") images.
	while(Fl::check()) {
		drawProgress(1);
		if (rendered == true) {
			rendered = false;
			break;
		}
	}
	// fl_color(FL_FOREGROUND_COLOR);
	// fl_draw("Hallo?", x(), y() - fl_descent());
}