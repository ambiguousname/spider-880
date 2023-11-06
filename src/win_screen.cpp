#include "win_screen.h"
#include "win_obj.h"
#include <sstream>
#include <util/window_management.h>
#include <FL/Fl.H>

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
	// test->scale(vec3(0.5f));
	// test->translate(vec3(0.0f, 0.0f, 2.0f));
}

void WinScreen::glDraw(const mat4& projection, const mat4& view, float time) {
	tick++;
	test->rotate(radians(0.1f), vec3(1.0f, 1.0f, 1.0f));
	test->draw(projection, view, time);
	// camera.translate(vec3(0.0f, 0.0f, -0.1f));
	if (tick > 600) {
		fullscreen();
		// Adding this to the main thread makes it memory safe to close:
		Fl::add_timeout(1.0, WindowManagement::hide_all_windows);
	}
}