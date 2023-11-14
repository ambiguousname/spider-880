#pragma once
#include "spider_navigator/page.h"
#include <spider/policies.h>
class MurderBlogPart1HTMLWindow : public HTMLWindow {
	public:
	MurderBlogPart1HTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MurderBlogPart1HTMLWindow(x, y, w, h);
	}
};
