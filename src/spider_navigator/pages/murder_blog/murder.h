#pragma once
#include <engounge/index.h>
#include "spider_navigator/page.h"
#include <spider/policies.h>
#include <murder_blog/index.h>
#include <cool_myths/theend.h>
class MurderBlogMurderHTMLWindow : public HTMLWindow {
	public:
	MurderBlogMurderHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MurderBlogMurderHTMLWindow(x, y, w, h);
	}
};
