#pragma once
#include <cool_myths/scream.h>
#include "spider_navigator/page.h"
#include <cool_myths/theend.h>
class CoolMythsIndexHTMLWindow : public HTMLWindow {
	public:
	CoolMythsIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new CoolMythsIndexHTMLWindow(x, y, w, h);
	}
};
