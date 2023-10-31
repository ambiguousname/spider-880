#pragma once
#include <mirror/index.h>
#include <ubbs/ubulletin.h>
#include "spider_navigator/page.h"
#include <ubbs/bulletin.h>
class UbbsIndexHTMLWindow : public HTMLWindow {
	public:
	UbbsIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new UbbsIndexHTMLWindow(x, y, w, h);
	}
};
