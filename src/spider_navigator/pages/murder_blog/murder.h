#pragma once
#include <cool_myths/theend.h>
#include "spider_navigator/page.h"
class MurderBlogMurderHTMLWindow : public HTMLWindow {
	public:
	MurderBlogMurderHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MurderBlogMurderHTMLWindow(x, y, w, h);
	}
};
