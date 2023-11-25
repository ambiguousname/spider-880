#pragma once
#include "../gl.h"
#include "opengl_shader.h"
#include "opengl_obj_geometry.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <vector>
#include <memory>
#include <iostream>

using namespace glm;

struct Vertex {
	vec4 position;
	vec3 normal;
	vec2 texcoord;
};

class Object {
	protected:
	mat4 model = mat4(1.0f);

	std::vector<std::shared_ptr<ObjectGeometry>> geometries;
	// We use vec4 for easy matrix math:
	std::vector<vec3> normals;
	std::vector<vec2> texcoords;

	std::vector<Vertex> vertices;
	
	GLuint vertices_vbo;

	// These should be set in a shader GLSL:
	GLuint position_idx = 0;
	GLuint normal_idx = 1;
	GLuint texcoord_idx = 2;

	void update_buffers();

	void load_from_stream(std::istream &in);

	public:
	Object(const char* filename);
	Object(std::istream &in);
	Object() {}
	~Object();

	void setShader(size_t index, std::shared_ptr<Shader> s) {
		if (index < geometries.size()) {
			geometries[index]->setShader(s);
		} else {
			std::cerr << "Invalid shader index " << index << std::endl;
		}
	}

	void initialize();
	void draw(const mat4& projection, const mat4& view, float time=0);

	void scale(vec3 amount) {
		model = glm::scale(model, amount);
	}
	void translate(vec3 amount) {
		model = glm::translate(model, amount);
	}
	void rotate(float angle, vec3 axis) {
		model = glm::rotate(model, angle, axis);
	}
};