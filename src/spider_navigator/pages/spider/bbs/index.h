#pragma once
#include <spider/bbs/announcements.h>
#include <mirror/index.h>
#include "spider_navigator/page.h"
#include <spider/bbs/messages.h>
class SpiderBbsIndexHTMLWindow : public HTMLWindow {
	public:
	SpiderBbsIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderBbsIndexHTMLWindow(x, y, w, h);
	}
};
