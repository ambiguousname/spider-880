#pragma once
#include "spider_navigator/page.h"
class LschiffIndexHTMLWindow : public HTMLWindow {
	public:
	LschiffIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new LschiffIndexHTMLWindow(x, y, w, h);
	}
};
