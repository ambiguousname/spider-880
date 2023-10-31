#pragma once
#include "spider_navigator/page.h"
#include <murder_blog/part1.h>
#include <spider/index.h>
#include <murder_blog/murder.h>
#include <star_information_systems/index.h>
class MurderBlogIndexHTMLWindow : public HTMLWindow {
	public:
	MurderBlogIndexHTMLWindow(int x, int y, int w, int h);
	static HTMLWindow* createWindow(int x, int y, int w, int h) {
		return new MurderBlogIndexHTMLWindow(x, y, w, h);
	}
};
