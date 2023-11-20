#pragma once
#include <mirror/index.h>
#include "spider_navigator/page.h"
class SpiderBbsAnnouncementsHTMLWindow : public HTMLWindow {
	public:
	SpiderBbsAnnouncementsHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderBbsAnnouncementsHTMLWindow(x, y, w, h);
	}
};
