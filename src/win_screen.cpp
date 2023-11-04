#include "win_screen.h"
WinScreen::WinScreen() : Fl_Gl_Window(300, 300, "You Win :)"), test("test.obj") {
	mode(FL_RGB | FL_OPENGL3);
	end();
	show();
	fullscreen();
}

void WinScreen::draw() {
	if (!valid()) {
		glLoadIdentity();
		glViewport(0,0,w(),h());
		glOrtho(-w(),w(),-h(),h(),-1,1);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	test.draw();
}