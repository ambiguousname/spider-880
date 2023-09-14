#pragma once

#include <FL/Fl_Image.H>
#include <FL/Fl_Widget.H>

class ImageBox : public Fl_Widget {
	void draw();

	void drawProgress(int speed);

	int draw_cursor_x = 0;
	int draw_cursor_y = 0;

	Fl_Image *image;
	const char* image_buffer;

	bool rendered = false;
	public:
	ImageBox(const char* image_loc, int x, int y, int w, int h);
	~ImageBox();
};