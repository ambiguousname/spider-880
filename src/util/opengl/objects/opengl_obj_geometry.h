#pragma once
#include "../gl.h"
#include "opengl_shader.h"

#include <memory>
#include <vector>

#include <glm/glm.hpp>

using namespace glm;

struct Vertex {
	vec4 position;
	vec3 normal;
	vec2 texcoord;
};

class ObjectGeometry {
	protected:
	std::shared_ptr<Shader> shader;
	GLuint elements_ibo;

	std::vector<GLushort> elements;

	public:
	~ObjectGeometry();

	void update_from_element_line(std::string line, std::vector<Vertex>& vertices, const std::vector<vec3>& normals, const std::vector<vec2>& texcoords);

	void initialize();
	void update_buffers();
	void draw(const mat4& model, const mat4& projection, const mat4& view, float time);

	void setShader(std::shared_ptr<Shader> s) {
		shader = s;
	}
};