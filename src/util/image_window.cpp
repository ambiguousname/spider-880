#include "image_window.h"

ImageWindow::ImageWindow(const char* image_loc, int w, int h, const char* title) : Fl_Window(w, h, title) {
	this->color(FL_BLACK);
}