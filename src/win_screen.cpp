#include "win_screen.h"
#include "win_obj.h"
#include <sstream>

WinScreen::WinScreen() : GlWindow(0, 0, 300, 300, "You Win :)") {
	std::istringstream in(win_obj);
	test = new Object(in);
	test->translate(vec3(0, 0, 0.5));
	std::shared_ptr<Shader> base(std::make_shared<Shader>("assets/shaders/vertex/base.glsl", "assets/shaders/frag/base.glsl"));
	test->setShader(base);
	mode(FL_RGB | FL_DEPTH | FL_OPENGL3);
	end();
	show();
	fullscreen();
}

void WinScreen::initialize() {
	test->initialize();
}

void WinScreen::glDraw(const mat4& projection, const mat4& view) {
	test->rotate(radians(1.0f), vec3(0.0f, 1.0f, 0.0f));
	test->draw(projection, view);
}