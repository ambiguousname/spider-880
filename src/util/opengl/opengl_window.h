#pragma once
#include "gl.h"
#include <FL/Fl_Gl_Window.H>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

using namespace glm;

class Camera {
	protected:
	mat4 projection;
	mat4 view;

	vec3 position = vec3(0.0f, 0.0f, -3.0f);
	vec3 forward = vec3(0.0f, 0.0f, 1.0f);
	vec3 up = vec3(0.0f, 1.0f, 0.0f);

	float fov;
	float nearZ;
	float farZ;
	float w;
	float h;

	public:
	Camera(float _w, float _h, float _fov=45.0f, float _nearZ=0.1f, float _farZ=100.0f) {
		fov = _fov;
		nearZ = _nearZ;
		farZ = _farZ;
		w = _w;
		h = _h;

		updateProjection();
		update();
	}
	Camera() {}

	void updateProjection() {
		projection = glm::perspective(radians(fov), w/h, nearZ, farZ);
	}
	void update() {
		view = glm::lookAt(position, position + forward, up);
	}

	void getCameraMatrices(mat4& out_projection, mat4& out_view) const {
		out_projection = projection;
		out_view = view;
	}

	void translate(vec3 add) {
		position += add;
	}
};

class GlWindow : public Fl_Gl_Window {
	protected:
	Camera camera;

	static void Timer_CB(void* self);

	public:
	GlWindow(int x, int y, int w, int h, const char* l=0);

	void draw() override;
	int handle(int event) override;

	void hide() override;

	const Camera getCamera() const {
		return camera;
	}

	virtual void initialize() = 0;
	virtual void glDraw(const mat4& projection, const mat4& view) = 0;
};