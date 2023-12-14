#pragma once
#include "spider_navigator/page.h"
#include <mirror/index.h>
class UbbsBulletinHTMLWindow : public HTMLWindow {
	public:
	UbbsBulletinHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new UbbsBulletinHTMLWindow(x, y, w, h);
	}
};
