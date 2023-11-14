#pragma once
#include "spider_navigator/page.h"
#include <mirror/index.h>
#include <spider/policies.h>
class UbbsUbulletinHTMLWindow : public HTMLWindow {
	public:
	UbbsUbulletinHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new UbbsUbulletinHTMLWindow(x, y, w, h);
	}
};
