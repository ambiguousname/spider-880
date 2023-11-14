#pragma once
#include "spider_navigator/page.h"
#include <murder_blog/index.h>
#include <spider/policies.h>
#include <engounge/index.h>
#include <cool_myths/theend.h>
class MurderBlogMurderHTMLWindow : public HTMLWindow {
	public:
	MurderBlogMurderHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MurderBlogMurderHTMLWindow(x, y, w, h);
	}
};
