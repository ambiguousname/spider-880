#pragma once
#include <murder_blog/index.h>
#include "spider_navigator/page.h"
#include <history/index.h>
#include <spider/policies.h>
class EngoungeIndexHTMLWindow : public HTMLWindow {
	public:
	EngoungeIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new EngoungeIndexHTMLWindow(x, y, w, h);
	}
};
