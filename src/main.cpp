#include <FL/Fl.H>
#include "spider_navigator/pages/murder_blog/pages.h"

int main(int argc, char **argv) {
	MurderBlogIndexHTMLPage::draw();

	// Fl::add_timeout(0.01, draw_img);
	return Fl::run();
}