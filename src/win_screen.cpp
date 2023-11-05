#include "win_screen.h"
#include "win_obj.h"
#include <sstream>

WinScreen::WinScreen() : Fl_Gl_Window(300, 300, "You Win :)") {
	std::istringstream in(win_obj);
	test = new Object(in);
	mode(FL_RGB | FL_OPENGL3);
	end();
	show();
	fullscreen();
}

int WinScreen::handle(int event) {
	#ifndef __APPLE__
	static int first = 1;
	if (first && event == FL_SHOW && shown()) {
		first = 0;
		make_current();
		glewInit(); // defines pters to functions of OpenGL V 1.2 and above
		test->initialize();
	}
	#endif
}

void WinScreen::draw() {
	if (!valid()) {
		glLoadIdentity();
		glViewport(0,0,w(),h());
		glOrtho(-w(),w(),-h(),h(),-1,1);
		glClearColor(1, 1, 1, 1);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	test->draw();
}