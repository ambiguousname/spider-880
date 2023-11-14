#pragma once
#include "spider_navigator/page.h"
#include <spider/policies.h>
#include <star_information_systems/index.h>
class FivecoolbeansIndexHTMLWindow : public HTMLWindow {
	public:
	FivecoolbeansIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new FivecoolbeansIndexHTMLWindow(x, y, w, h);
	}
};
