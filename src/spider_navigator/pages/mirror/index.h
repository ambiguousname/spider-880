#pragma once
#include <spider/bbs/index.h>
#include <ubbs/index.h>
#include "spider_navigator/page.h"
class MirrorIndexHTMLWindow : public HTMLWindow {
	public:
	MirrorIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MirrorIndexHTMLWindow(x, y, w, h);
	}
};
