#pragma once
#include "spider_navigator/page.h"
class StarInformationSystemsLastresortHTMLWindow : public HTMLWindow {
	public:
	StarInformationSystemsLastresortHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new StarInformationSystemsLastresortHTMLWindow(x, y, w, h);
	}
};
