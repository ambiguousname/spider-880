#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "util/image_box.h"
#include <filesystem>
#include "spider_navigator/pages/murder_blog/pages.h"

int main(int argc, char **argv) {
	MurderBlogIndexHTMLPage::draw();

	// Fl::add_timeout(0.01, draw_img);
	return Fl::run();
}