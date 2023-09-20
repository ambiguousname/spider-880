#pragma once
#include "spider_navigator/page.h"
class CoolMythsScreamHTMLWindow : public HTMLWindow {
	public:
	CoolMythsScreamHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new CoolMythsScreamHTMLWindow(x, y, w, h);
	}
};
class CoolMythsTheendHTMLWindow : public HTMLWindow {
	public:
	CoolMythsTheendHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new CoolMythsTheendHTMLWindow(x, y, w, h);
	}
};
