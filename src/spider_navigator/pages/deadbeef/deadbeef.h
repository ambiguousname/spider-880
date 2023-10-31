#pragma once
#include <FL/gl.h>
#include "spider_navigator/page.h"
class DeadbeefDeadbeefHTMLWindow : public HTMLWindow {
	private:
	void draw();
	public:
	DeadbeefDeadbeefHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new DeadbeefDeadbeefHTMLWindow(x, y, w, h);
	}
};
