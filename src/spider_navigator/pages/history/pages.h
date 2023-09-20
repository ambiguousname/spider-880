#pragma once
#include "spider_navigator/page.h"
class HistoryRoriksendHTMLWindow : public HTMLWindow {
	public:
	HistoryRoriksendHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h);
};
