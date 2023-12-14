#pragma once
#include <gertwig_blog/index.h>
#include <spider/policies.h>
#include "spider_navigator/page.h"
class GertwigBlogNavsabHTMLWindow : public HTMLWindow {
	public:
	GertwigBlogNavsabHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new GertwigBlogNavsabHTMLWindow(x, y, w, h);
	}
};
