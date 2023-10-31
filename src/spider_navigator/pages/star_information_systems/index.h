#pragma once
#include <lschiff/index.h>
#include "spider_navigator/page.h"
#include <star_information_systems/system.h>
#include <star_information_systems/lastresort.h>
#include <fivecoolbeans/index.h>
class StarInformationSystemsIndexHTMLWindow : public HTMLWindow {
	public:
	StarInformationSystemsIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new StarInformationSystemsIndexHTMLWindow(x, y, w, h);
	}
};
