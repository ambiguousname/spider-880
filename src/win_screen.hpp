#pragma once
#include <util/opengl/opengl_window.hpp>
#include <util/opengl/objects/opengl_obj.hpp>
#include <util/sound.hpp>
#include <time.h>

class WinScreen : public GlWindow {
	protected:
	Object* test;
	time_t tick;

	SoundManager::Sound endSound;
	
	public:
	WinScreen();
	~WinScreen() {
		delete test;
	}

	void initialize() override;
	void glDraw(const mat4& projection, const mat4& view, float time) override;
};