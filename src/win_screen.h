#pragma once
#include <FL/Fl_Gl_Window.H>
#include <util/opengl/gl.h>
#include <util/opengl/opengl_obj.h>

class WinScreen : public Fl_Gl_Window {
	protected:
	Object* test;
	
	public:
	WinScreen();
	~WinScreen() {
		delete test;
	}
	void draw();
	int handle(int event);
};