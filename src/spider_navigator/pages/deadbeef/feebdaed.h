#pragma once
#include "spider_navigator/page.h"
class DeadbeefFeebdaedHTMLWindow : public HTMLWindow {
	public:
	DeadbeefFeebdaedHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new DeadbeefFeebdaedHTMLWindow(x, y, w, h);
	}
};
