#include "image_box.h"
#include "color.h"
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl.H>

ImageBox::ImageBox(const char* image_loc) {
	Fl_PNG_Image temp = Fl_PNG_Image(image_loc);
	
	const char* buf = temp.data()[0];

	char* new_buf = new char[temp.h() * temp.w() * temp.d()];
	for (int x = 0; x < temp.w(); x++) {
		for (int y = 0; y < temp.h(); y++) {
			long index = (y * temp.w() * temp.d()) + (x * temp.d());
			unsigned char r = *(buf + index);
			unsigned char g = *(buf + index + 1);
			unsigned char b = *(buf + index + 2);
			Fl_Color result = rgb_to_palette(r, g, b);

			unsigned char out_r, out_g, out_b;
			Fl::get_color(result, out_r, out_g, out_b);

			new_buf[index] = out_r;
			new_buf[index + 1] = out_g;
			new_buf[index + 2] = out_b;
		}
	}

	full_image = std::make_unique<Fl_PNG_Image>(nullptr, (const unsigned char*) new_buf, sizeof(buf)/sizeof(char));
}

void ImageBox::prepareDraw(int x, int y, int w, int h) {
	image.reset();
	image = std::unique_ptr<Fl_Image>(full_image->copy(w, h));
	image_buffer = image->data()[0];
	start_x = x;
	start_y = y;
	draw_cursor_x = 0;
	draw_cursor_y = 0;
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
			cached = true;
			return;
		}
		long index = (draw_cursor_y * image->w() * image->d()) + (draw_cursor_x * image->d());
		
		unsigned char r = *(image_buffer + index);
		unsigned char g = *(image_buffer + index + 1);
		unsigned char b = *(image_buffer + index + 2);

		fl_color(r, g, b);
		fl_point(draw_cursor_x + start_x, draw_cursor_y + start_y);
		draw_cursor_x += 1;
	}
}

void ImageBox::draw() {
	// image->draw(start_x, start_y);
	if (cached) {
		// image->draw(start_x, start_y);
	} else {
		// while(!cached) {
		// 	drawProgress(1);
		// }
	}
}