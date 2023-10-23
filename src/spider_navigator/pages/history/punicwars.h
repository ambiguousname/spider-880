#pragma once
#include <history/index.h>
#include "spider_navigator/page.h"
class HistoryPunicwarsHTMLWindow : public HTMLWindow {
	public:
	HistoryPunicwarsHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new HistoryPunicwarsHTMLWindow(x, y, w, h);
	}
};
