#pragma once
#include <FL/Fl_Gl_Window.H>
#include <util/opengl/gl.h>
#include <util/opengl/opengl_obj.h>
#include <glm/ext/matrix_clip_space.hpp>

class WinScreen : public Fl_Gl_Window {
	protected:
	Object* test;

	mat4 proj;
	mat4 view = mat4(1.0);
	
	public:
	WinScreen();
	~WinScreen() {
		delete test;
	}
	void draw();
	int handle(int event);
};