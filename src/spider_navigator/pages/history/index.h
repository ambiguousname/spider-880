#pragma once
#include "spider_navigator/page.h"
#include <history/roriksend.h>
#include <history/punicwars.h>
class HistoryIndexHTMLWindow : public HTMLWindow {
	public:
	HistoryIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new HistoryIndexHTMLWindow(x, y, w, h);
	}
};
