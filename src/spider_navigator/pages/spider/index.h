#pragma once
#include "spider_navigator/page.h"
#include <spider/policies.h>
#include <spider/bbs/index.h>
#include <spider/about_us.h>
class SpiderIndexHTMLWindow : public HTMLWindow {
	public:
	SpiderIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderIndexHTMLWindow(x, y, w, h);
	}
};
