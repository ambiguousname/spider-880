#pragma once
#include "spider_navigator/page.h"
#include <gertwig_blog/navsab.h>
class GertwigBlogIndexHTMLWindow : public HTMLWindow {
	public:
	GertwigBlogIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new GertwigBlogIndexHTMLWindow(x, y, w, h);
	}
};
