#include "win_screen.h"
#include "win_obj.h"
#include <sstream>

WinScreen::WinScreen() : Fl_Gl_Window(300, 300, "You Win :)") {
	std::istringstream in(win_obj);
	test = new Object(in);
	// test->scale(vec3(10.0f));
	std::shared_ptr<Shader> base(std::make_shared<Shader>("assets/shaders/vertex/base.glsl", "assets/shaders/frag/base.glsl"));
	test->setShader(base);
	mode(FL_RGB | FL_DEPTH | FL_OPENGL3);
	end();
	show();
	// fullscreen();
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
	redraw();
	return Fl_Gl_Window::handle(event);
}

void WinScreen::draw() {
	if (!valid()) {
		glLoadIdentity();
		glViewport(0,0,w(),h());
		glOrtho(-w(),w(),-h(),h(),-1,100);

		// GLfloat mat_ambient[]    = { 1.0, 1.0, 1.0, 1.0 };  // RGBA
		// GLfloat mat_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };  // RGBA
		// GLfloat mat_specular[]   = { 1.0, 1.0, 1.0, 1.0 };  // RGBA
		// GLfloat light_position[] = { 5.0, 5.0, 0.0, 0.0 };  // XYZ
		// glClearColor(0.0, 0.0, 0.4, 0.0);                   // bg color
		// glShadeModel(GL_SMOOTH);
		
		// glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
		// glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
		// glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
		// glMaterialf(GL_FRONT,  GL_SHININESS, 20.0);
		// glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		// glEnable(GL_LIGHTING);
		// glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		// glDepthFunc(GL_ALWAYS); 
		// glClearColor(1, 1, 1, 1);
	}
	//clear color and depth buffer 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	test->rotate(radians(1.0f), vec3(0.0f, 1.0f, 0.0f));
    
	test->draw();
}