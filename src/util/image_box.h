#pragma once

#include <FL/Fl_Image.H>
#include <FL/Fl_Widget.H>
#include <memory>
class PaletteImage {
	protected:
	uchar* img_dat;
	Fl_RGB_Image* cached_img;

	int _w;
	int _h;
	int _d;
	int _ld;
	bool cached = false;
	public:
	PaletteImage(int w, int h, int d, int ld);
	Fl_Color drawPixel(int x, int y, uchar r, uchar g, uchar b);
	void finishDraw();
	Fl_Image* copy(int w, int h);
	bool isCached() { return cached; }
	~PaletteImage();
};

class ImageBox {

	void drawProgress(int speed);

	int draw_cursor_x = 0;
	int draw_cursor_y = 0;

	int start_x = 0;
	int start_y = 0;

	// Full image, without scaling down to width and height.
	std::unique_ptr<Fl_Image> full_image;
	// Image scaled down to width and height.
	std::unique_ptr<Fl_Image> image;
	const char* image_buffer;

	std::unique_ptr<PaletteImage> saved_img;
	public:
	void getFullDimensions(int& out_w, int& out_h) { out_w = full_image->w(); out_h = full_image->h(); }
	void prepareDraw(int x, int y, int w, int h);
	void draw();
	ImageBox(const char* image_loc);
	~ImageBox();
};