#include "image_box.h"
#include "color.h"
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl.H>

PaletteImage::PaletteImage(int w, int h, int d, int ld) {
	_w = w;
	_h = h;
	_d = d;
	_ld = ld;
	img_dat = new uchar[w * h * d];
}

Fl_Color PaletteImage::drawPixel(int x, int y, uchar r, uchar g, uchar b) {
	int i = (y * _w * _d) + (x * _d);
	Fl_Color p = rgb_to_palette(r, g, b);

	uchar p_r, p_g, p_b;
	Fl::get_color(p, p_r, p_g, p_b);
	img_dat[i] = p_r;
	img_dat[i + 1] = p_g;
	img_dat[i + 2] = p_b;
	return p;
}

Fl_Image* PaletteImage::copy(int w, int h) {
	return cached_img->copy(w, h);
}

void PaletteImage::finishDraw() {
	if (!cached){
		cached = true;
		cached_img = new Fl_RGB_Image(img_dat, _w, _h, _d, _ld);
	}
}

PaletteImage::~PaletteImage() {
	delete img_dat;
	delete cached_img;
}

ImageBox::ImageBox(const char* image_loc) {
	full_image = std::make_unique<Fl_PNG_Image>(image_loc);
}

void ImageBox::prepareDraw(int x, int y, int w, int h) {
	image.reset();
	
	if (saved_img == nullptr) {
		image = std::unique_ptr<Fl_Image>(full_image->copy(w, h));
		saved_img = std::make_unique<PaletteImage>(w, h, full_image->d(), full_image->ld());
		image_buffer = image->data()[0];
	} else {
		image = std::unique_ptr<Fl_Image>(saved_img->copy(w, h));
	}
	start_x = x;
	start_y = y;
	draw_cursor_x = 0;
	draw_cursor_y = 0;
}

ImageBox::~ImageBox() {
	image.reset();
	full_image.reset();
	saved_img.reset();
}

// Best-ish: New file type? Just insert the 4 extra bits for the palette somewhere.
// For PNGs, you could probably use transparency? (Should check how Fl_PNG_Image will read that though)
// Probably just easiest to pre-generate the image with the palette.
void ImageBox::drawProgress(int speed) {
	for (int i = 0; i < speed; i++) {
		if (draw_cursor_x >= image->w()) {
			draw_cursor_y += 1;
			draw_cursor_x = 0;
		}
		if (draw_cursor_y >= image->h()) {
			draw_cursor_x = 0;
			draw_cursor_y = 0;
			saved_img->finishDraw();

			auto new_img = std::unique_ptr<Fl_Image>(saved_img->copy(image->w(), image->h()));
			image.swap(new_img);
			new_img.reset();
			return;
		}
		long index = (draw_cursor_y * image->w() * image->d()) + (draw_cursor_x * image->d());
		
		unsigned char r = *(image_buffer + index);
		unsigned char g = *(image_buffer + index + 1);
		unsigned char b = *(image_buffer + index + 2);

		fl_color(r, g, b);
		
		if (!saved_img->isCached()) {
			Fl_Color result = saved_img->drawPixel(draw_cursor_x, draw_cursor_y, r, g, b);
			fl_color(result);
		}
		fl_point(draw_cursor_x + start_x, draw_cursor_y + start_y);
		draw_cursor_x += 1;
	}
}

void ImageBox::draw() {
	if (saved_img->isCached()) {
		image->draw(start_x, start_y);
	} else {
		while(!saved_img->isCached()) {
			drawProgress(1);
		}
	}
}