#pragma once
#include "gl.h"

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

using namespace glm;
class Object {
	protected:
	mat4x4 transform;

	// We use vec4 for easy matrix math:
	std::vector<vec4> vertices;
	std::vector<vec3> normals;
	std::vector<GLushort> elements;

	GLuint vertices_vbo;
	// Indices:
	GLuint elements_ibo;

	void update_buffers();

	void loadFromStream(std::istream &in);

	bool enabled = false;
	public:
	Object(const char* filename);
	Object(std::istream &in);
	Object() {}
	~Object();
	void draw();
};