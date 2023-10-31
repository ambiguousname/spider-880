#pragma once
#include <spider/index.h>
#include "spider_navigator/page.h"
#include <spider/about_us.h>
class SpiderPoliciesHTMLWindow : public HTMLWindow {
	public:
	SpiderPoliciesHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new SpiderPoliciesHTMLWindow(x, y, w, h);
	}
};
