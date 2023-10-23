#pragma once
#include <mirror/index.h>
#include "spider_navigator/page.h"
class SpiderBbsMessagesHTMLWindow : public HTMLWindow {
	public:
	SpiderBbsMessagesHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderBbsMessagesHTMLWindow(x, y, w, h);
	}
};
