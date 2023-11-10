#pragma once

#include <FL/Fl_Image.H>
#include <FL/Fl_Widget.H>
#include <memory>
class PaletteImage {
	protected:
	uchar* img_dat;

	uchar* img_resized = nullptr;

	int resized_w;
	int resized_h;

	int _w;
	int _h;
	int _d;
	bool cached = false;
	public:
	uchar* getImageDat() const { return img_dat; }
	int w() const { return _w; }
	int h() const { return _h; }
	int d() const { return _d; }

	void prepareDraw(int w, int h);
	void draw(int x, int y);

	PaletteImage(int w, int h, int d);
	Fl_Color drawPixel(int x, int y, uchar r, uchar g, uchar b);
	void finishDraw();
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
	std::unique_ptr<Fl_Image> downsized;
	const char* image_buffer;

	std::unique_ptr<PaletteImage> saved_img;
	public:
	void getFullDimensions(int& out_w, int& out_h) { out_w = full_image->w(); out_h = full_image->h(); }
	void prepareDraw(int x, int y, int w, int h);
	void draw();
	ImageBox(const char* image_loc);
	~ImageBox();
};