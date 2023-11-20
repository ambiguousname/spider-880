#pragma once
#include <history/roriksend.h>
#include <history/punicwars.h>
#include "spider_navigator/page.h"
class HistoryIndexHTMLWindow : public HTMLWindow {
	public:
	HistoryIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new HistoryIndexHTMLWindow(x, y, w, h);
	}
};
