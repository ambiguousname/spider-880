#pragma once
#include "spider_navigator/page.h"
#include <spider/policies.h>
#include <spider/index.h>
class SpiderAboutUsHTMLWindow : public HTMLWindow {
	public:
	SpiderAboutUsHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderAboutUsHTMLWindow(x, y, w, h);
	}
};
