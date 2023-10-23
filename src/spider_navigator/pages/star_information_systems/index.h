#pragma once
#include "spider_navigator/page.h"
#include <fivecoolbeans/index.h>
#include <lschiff/index.h>
class StarInformationSystemsIndexHTMLWindow : public HTMLWindow {
	public:
	StarInformationSystemsIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new StarInformationSystemsIndexHTMLWindow(x, y, w, h);
	}
};