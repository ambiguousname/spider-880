#pragma once
#include <deadbeef/deadbeefgl.h>
#include "spider_navigator/page.h"
class DeadbeefDeadbeefHTMLWindow : public HTMLWindow {
	protected:
	DeadbeefGL* gl_window;
	public:
	DeadbeefDeadbeefHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new DeadbeefDeadbeefHTMLWindow(x, y, w, h);
	}
};
