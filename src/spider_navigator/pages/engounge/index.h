#pragma once
#include "spider_navigator/page.h"
class EngoungeIndexHTMLWindow : public HTMLWindow {
	public:
	EngoungeIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new EngoungeIndexHTMLWindow(x, y, w, h);
	}
};
