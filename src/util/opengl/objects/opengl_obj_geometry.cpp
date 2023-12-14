#include "opengl_obj_geometry.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

ObjectGeometry::~ObjectGeometry() {
	shader.reset();
	glDeleteBuffers(1, &elements_ibo);
}

// Modified from https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
void ObjectGeometry::update_from_element_line(std::string line, std::vector<Vertex>& vertices, const std::vector<vec3>& normals, const std::vector<vec2>& texcoords) {
	if (line.substr(0, 2) == "f ") {
		std::istringstream s(line.substr(2));

		std::string token;
		const std::string delim = "/";
		
		// For .OBJ files, we have one space for each vertex.
		for (int i = 0; i < 3; i++) {
			s >> token;

			std::size_t pos = 0;
			int j = 0;

			do {
				pos = token.find(delim);

				std::string subtoken = token.substr(0, pos);
				token.erase(0, pos + delim.length());

				if (subtoken.size() <= 0) {
					continue;
				}

				GLushort item = std::stoi(subtoken);
				item--;
				switch(j) {
					case 0:
						elements.push_back(item);
					break;
					case 1:
						if (item < texcoords.size()) {
							vertices[elements.back()].texcoord = texcoords[item];
						}
					break;
					case 2:
						if (item < normals.size()) {
							// Should duplicate vertices if you want flat shading to avoid sharing normals (and arbitrary selection of normals)
							// Same with tex coords.
							vertices[elements.back()].normal = normals[item];
						}
					break;
					default:
						std::cerr << "Unexpected subtoken at index " << j << " with token " << token << " at line " << line << std::endl;
					break;
				}
				j++;
			}
			while(pos != std::string::npos);
		}
	}
}

void ObjectGeometry::initialize() {
	glGenBuffers(1, &elements_ibo);
	update_buffers();

	shader->initialize();
}

void ObjectGeometry::update_buffers() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_ibo);
	// Base on https://docs.gl/gl3/glDrawElements
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * elements.size(), &elements[0], GL_STATIC_DRAW);
}

void ObjectGeometry::draw(const mat4& model, const mat4& projection, const mat4& view, float time) {
	if (shader != nullptr){
		shader->useProgram();
	}

	if (shader != nullptr) {
		shader->setAttrs(glm::value_ptr(model), glm::value_ptr(projection), glm::value_ptr(view), time);
	}

	// Prepare to draw elements:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_ibo);
	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_SHORT, (void*)0);
}