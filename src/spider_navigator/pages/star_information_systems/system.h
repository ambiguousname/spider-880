#pragma once
#include "spider_navigator/page.h"
class StarInformationSystemsSystemHTMLWindow : public HTMLWindow {
	public:
	StarInformationSystemsSystemHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new StarInformationSystemsSystemHTMLWindow(x, y, w, h);
	}
};
