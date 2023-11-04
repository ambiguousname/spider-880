#pragma once
#include <FL/Fl_Gl_Window.H>
#include <util/gl.h>
class HTMLGLRender : public Fl_Gl_Window {
	public:
	HTMLGLRender(int x, int y, int w, int h, const char* title);
	virtual void draw() = 0;
};