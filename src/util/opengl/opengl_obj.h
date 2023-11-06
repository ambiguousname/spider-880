#pragma once
#include "gl.h"
#include "opengl_shader.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <memory>

using namespace glm;
class Object {
	protected:
	mat4 transform = mat4(1.0f);

	// We use vec4 for easy matrix math:
	std::vector<vec4> vertices;
	std::vector<vec3> normals;
	std::vector<GLushort> elements;

	GLuint vertices_vbo;
	// Indices:
	GLuint elements_ibo;
	// Attributes:
	GLuint attributes_vao;

	// These should be set in a shader:
	GLuint position_idx = 0;
	GLuint transform_idx = 1;

	std::shared_ptr<Shader> shader;

	void update_buffers();

	void loadFromStream(std::istream &in);

	public:
	Object(const char* filename);
	Object(std::istream &in);
	Object() {}
	~Object();

	void setShader(std::shared_ptr<Shader> s) {
		shader = s;
	}

	void initialize();
	void draw();

	void scale(vec3 amount) {
		transform = glm::scale(transform, amount);
	}
	void translate(vec3 amount) {
		transform = glm::translate(transform, amount);
	}
	void rotate(float angle, vec3 axis) {
		transform = glm::rotate(transform, angle, axis);
	}
};