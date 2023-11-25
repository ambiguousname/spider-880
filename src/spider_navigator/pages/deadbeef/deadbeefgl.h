#pragma once
#include <util/opengl/opengl_window.h>
#include <util/opengl/objects/opengl_obj.h>

class DeadbeefGL : public GlWindow {
	Object* ship;

	public:
	DeadbeefGL(int x, int y, int w, int h, const char* l=0);
	~DeadbeefGL() {
		delete ship;
	}

	void initialize() override;
	void glDraw(const mat4& projection, const mat4& view, float time) override;
};