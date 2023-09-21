#pragma once
#include "spider_navigator/page.h"
#include <cool_myths/pages.h>
class MurderBlogIndexHTMLWindow : public HTMLWindow {
	public:
	MurderBlogIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MurderBlogIndexHTMLWindow(x, y, w, h);
	}
};
