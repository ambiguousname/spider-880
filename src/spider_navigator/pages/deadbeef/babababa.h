#pragma once
#include "spider_navigator/page.h"
class DeadbeefBabababaHTMLWindow : public HTMLWindow {
	public:
	DeadbeefBabababaHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new DeadbeefBabababaHTMLWindow(x, y, w, h);
	}
};
