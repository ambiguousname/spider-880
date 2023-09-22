#pragma once
#include <cool_myths/pages.h>
#include "spider_navigator/page.h"
class MurderBlogIndexHTMLWindow : public HTMLWindow {
	public:
	MurderBlogIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MurderBlogIndexHTMLWindow(x, y, w, h);
	}
};
