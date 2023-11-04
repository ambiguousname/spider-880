#pragma once
#include <FL/Fl_Gl_Window.H>
#include <util/gl.h>
#include <util/opengl_obj.h>

class WinScreen : public Fl_Gl_Window {
	protected:
	Object test;
	
	public:
	WinScreen();
	void draw();
};