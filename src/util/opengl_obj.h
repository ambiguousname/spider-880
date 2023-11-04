#pragma once
#include "gl.h"

#include <glm/glm.hpp>
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

	public:
	
	Object(const char* filename);
	~Object();
	void draw();
};