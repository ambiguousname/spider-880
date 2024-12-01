#include "win_screen.hpp"
#include "win_obj.hpp"
#include <sstream>
#include <util/window_management.hpp>
#include <FL/Fl.H>
#include <FL/fl_message.H>

#include <util/base_sounds.hpp>

WinScreen::WinScreen() : GlWindow(0, 0, 300, 300, "You Win :)") {
	std::istringstream in(win_obj);
	test = new Object(in);
	test->translate(vec3(0, 0, 0.5));
	std::shared_ptr<Shader> base(std::make_shared<Shader>("assets/shaders/vertex/base.glsl", "assets/shaders/frag/base.glsl"));
	test->setShader(0, base);
	mode(FL_RGB | FL_DEPTH | FL_OPENGL3);
	end();
	show();
	fullscreen();

	SoundManager::Load("./assets/startup.wav", endSound);
	endSound.setLoop(true);
	endSound.setPitch(0.1f);
	endSound.play();
}

void WinScreen::initialize() {
	test->initialize();
	// test->scale(vec3(0.5f));
	// test->translate(vec3(0.0f, 0.0f, 2.0f));
}

void winScreen(void*) {
	WindowManagement::hide_all_windows();
	errorSound();
	fl_alert("Well, you win. Congrats.");
}

bool isClosing = false;

void WinScreen::glDraw(const mat4& projection, const mat4& view, float time) {
	tick++;
	test->rotate(radians(0.1f), vec3(1.0f, 1.0f, 1.0f));
	test->draw(projection, view, time);
	// camera.translate(vec3(0.0f, 0.0f, -0.1f));
	if (!isClosing && tick > 600) {
		isClosing = true;
		endSound.stop();
		// Adding this to the main thread makes it memory safe to close:
		Fl::add_timeout(1.0, winScreen);
	}
}