#pragma once
#include <util/opengl/opengl_window.h>
#include <util/opengl/objects/opengl_obj.h>

class FeebdaedGL : public GlWindow {
	Object* cave;
	Object* person;

	public:
	FeebdaedGL(int x, int y, int w, int h, const char* l=0);
	~FeebdaedGL() {
		delete cave;
		delete person;
	}

	void initialize() override;
	void glDraw(const mat4& projection, const mat4& view, float time) override;
};