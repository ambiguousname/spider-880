#pragma once
#include "spider_navigator/page.h"
#include <mirror/index.h>
#include <spider/policies.h>
class SpiderBbsMessagesHTMLWindow : public HTMLWindow {
	public:
	SpiderBbsMessagesHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderBbsMessagesHTMLWindow(x, y, w, h);
	}
};
