#pragma once

#include <FL/Fl_Window.H>

class ImageWindow : public Fl_Window {
	public:
	ImageWindow(const char* image_loc, int w, int h, const char* title);
};