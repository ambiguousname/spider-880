#pragma once
#include <util/opengl/opengl_window.h>
#include <util/opengl/opengl_obj.h>

class WinScreen : public GlWindow {
	protected:
	Object* test;
	int tick = 0;
	
	public:
	WinScreen();
	~WinScreen() {
		delete test;
	}

	void initialize() override;
	void glDraw(const mat4& projection, const mat4& view) override;
};