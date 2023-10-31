#pragma once
#include <spider/index.h>
#include "spider_navigator/page.h"
#include <spider/policies.h>
class SpiderAboutUsHTMLWindow : public HTMLWindow {
	public:
	SpiderAboutUsHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderAboutUsHTMLWindow(x, y, w, h);
	}
};
