#include "image_box.hpp"
#include "color.hpp"
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl.H>

PaletteImage::PaletteImage(int w, int h, int d) {
	_w = w;
	_h = h;
	_d = d;
	img_dat = new uchar[w * h * d];
}

Fl_Color PaletteImage::drawPixel(int x, int y, uchar r, uchar g, uchar b) {
	long i = (y * _w * _d) + (x * _d);
	Fl_Color p = rgb_to_palette(r, g, b);

	uchar p_r, p_g, p_b;
	Fl::get_color(p, p_r, p_g, p_b);
	img_dat[i] = p_r;
	img_dat[i + 1] = p_g;
	img_dat[i + 2] = p_b;
	return p;
}

void PaletteImage::prepareDraw(int w, int h) {
	// Based on https://github.com/fltk/fltk/blob/master/src/Fl_Image.cxx
	if (img_resized != nullptr) {
		delete img_resized;
		img_resized = nullptr;
	}
	img_resized = new uchar[w * h * _d];

	resized_w = w;
	resized_h = h;


	int xmod, ymod, xstep, ystep;
	xmod = _w % resized_w;
	xstep = (_w / resized_w) * _d;
	ymod = _h % resized_h;
	ystep = _h / resized_h;

	int line_step = _w * _d;

	uchar* new_ptr;
	int dy, sy, yerr;

	int dx, xerr;
	const uchar* old_ptr;

	int channel_number;
	for (dy = resized_h, sy = 0, yerr = resized_h, new_ptr = img_resized; dy > 0; dy--) {
		for (dx = resized_w, xerr = resized_w, old_ptr = img_dat + sy * line_step; dx > 0; dx--) {
			for (channel_number=0; channel_number < _d; channel_number++) *new_ptr++ = old_ptr[channel_number];

			old_ptr += xstep;
			xerr -= xmod;

			if (xerr <= 0) {
				xerr += resized_w;
				old_ptr += _d;
			}
		}

		sy += ystep;
		yerr -= ymod;
		if (yerr <= 0) {
			yerr += resized_h;
			sy++;
		}
	}
}

void PaletteImage::draw(int x, int y) {
	fl_draw_image(img_resized, x, y, resized_w, resized_h, _d);
}

void PaletteImage::finishDraw() {
	if (!cached){
		cached = true;
	}
}

PaletteImage::~PaletteImage() {
	delete img_dat;
	delete img_resized;
}

ImageBox::ImageBox(const char* image_loc) {
	full_image = std::make_unique<Fl_PNG_Image>(image_loc);
}

void ImageBox::prepareDraw(int x, int y, int w, int h) {
	if (saved_img == nullptr) {
		downsized = std::unique_ptr<Fl_Image>(full_image->copy(w, h));
		saved_img = std::make_unique<PaletteImage>(w, h, full_image->d());
		image_buffer = downsized->data()[0];
	} else {
		saved_img->prepareDraw(w, h);
	}
	start_x = x;
	start_y = y;
	draw_cursor_x = 0;
	draw_cursor_y = 0;
}

ImageBox::~ImageBox() {
	downsized.reset();
	full_image.reset();
	saved_img.reset();
}

// Best-ish: New file type? Just insert the 4 extra bits for the palette somewhere.
// For PNGs, you could probably use transparency? (Should check how Fl_PNG_Image will read that though)
// Probably just easiest to pre-generate the image with the palette.
void ImageBox::drawProgress(int speed) {
	for (int i = 0; i < speed; i++) {
		if (draw_cursor_x >= downsized->w()) {
			draw_cursor_y += 1;
			draw_cursor_x = 0;
		}
		if (draw_cursor_y >= downsized->h()) {
			draw_cursor_x = 0;
			draw_cursor_y = 0;
			saved_img->finishDraw();
			return;
		}
		long index = (draw_cursor_y * downsized->w() * downsized->d()) + (draw_cursor_x * downsized->d());
		
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
		saved_img->draw(start_x, start_y);
	} else {
		while(!saved_img->isCached()) {
			drawProgress(1);
		}
	}
}