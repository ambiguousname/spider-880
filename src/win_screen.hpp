#pragma once
#include <util/opengl/opengl_window.hpp>
#include <util/opengl/objects/opengl_obj.hpp>
#include <util/sound.hpp>

class WinScreen : public GlWindow {
	protected:
	Object* test;
	int tick = 0;

	SoundManager::Sound endSound;
	
	public:
	WinScreen();
	~WinScreen() {
		delete test;
	}

	void initialize() override;
	void glDraw(const mat4& projection, const mat4& view, float time) override;
};