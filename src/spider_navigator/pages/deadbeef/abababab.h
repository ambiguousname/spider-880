#pragma once
#include "spider_navigator/page.h"
class DeadbeefAbabababHTMLWindow : public HTMLWindow {
	public:
	DeadbeefAbabababHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new DeadbeefAbabababHTMLWindow(x, y, w, h);
	}
};
