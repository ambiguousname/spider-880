#include "image_box.h"
#include "color.h"
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl.H>

ImageBox::ImageBox(const char* image_loc) {
	full_image = std::make_unique<Fl_PNG_Image>(image_loc);
}

void ImageBox::prepareDraw(int x, int y, int w, int h) {
	image.reset();
	image = std::unique_ptr<Fl_Image>(full_image->copy(w, h));
	image_buffer = image->data()[0];
	start_x = draw_cursor_x = x;
	start_y = draw_cursor_y = y;
}

ImageBox::~ImageBox() {
	image.reset();
	full_image.reset();
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
		fl_point(draw_cursor_x + start_x, draw_cursor_y + start_y);
		draw_cursor_x += 1;
	}
}

void ImageBox::draw() {
	// TODO: More efficient code for damaged or fully drawn ("cached") images.
	if (rendered) {
		image->draw(start_x, start_y);
	} else {
		while(Fl::check()) {
			drawProgress(1);
		}
	}
}