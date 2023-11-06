#include "opengl_window.h"
#include <FL/Fl.H>

void Timer_CB(void* screen) {
	((GlWindow*)screen)->redraw();
	Fl::repeat_timeout(1.0/60.0, Timer_CB, screen);
}

GlWindow::GlWindow(int x, int y, int w, int h, const char* l) : Fl_Gl_Window(x, y, w, h, l) {
	mode(FL_RGB | FL_DEPTH | FL_OPENGL3);
}

int GlWindow::handle(int event) {
	#ifndef __APPLE__
	static int first = 1;
	if (first && event == FL_SHOW && shown()) {
		first = 0;
		make_current();
		glewInit(); // defines pters to functions of OpenGL V 1.2 and above
		initialize();
		// Render redraw:
		Fl::add_timeout(1.0/60.0, Timer_CB, (void*) this);
	}
	#endif
	return Fl_Gl_Window::handle(event);
}

void GlWindow::draw() {
	if(!valid()) {
		glLoadIdentity();
		glViewport(0, 0, w(), h());

		camera = Camera(w(), h());

		glEnable(GL_DEPTH_TEST);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 projection, view;
	camera.getCameraMatrices(projection, view);
	glDraw(projection, view);
}