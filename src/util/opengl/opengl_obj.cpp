#include "opengl_obj.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Material::~Material() {
	shader.reset();
	glDeleteBuffers(1, &elements_ibo);
}

// Modified from https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
void Material::update_from_element_line(std::string line, std::vector<Vertex>& vertices, const std::vector<vec3>& normals, const std::vector<vec2>& uvs) {
	if (line.substr(0, 2) == "f ") {
		std::istringstream s(line.substr(2));

		std::string token;
		const std::string delim = "/";
		
		// For .OBJ files, we have one space for each 
		for (int i = 0; i < 3; i++) {
			s >> token;

			std::size_t pos = 0;
			int j = 0;

			do {
				pos = token.find(delim);

				std::string subtoken = token.substr(0, pos);
				token.erase(0, pos + delim.length());

				GLushort item = std::stoi(subtoken);
				item--;
				switch(j) {
					case 0:
						elements.push_back(item);
					break;
					case 1:
						// Should duplicate vertices if you want flat shading to avoid sharing normals (and arbitrary selection of normals)
						vertices[elements.back()].normal = normals[item];
					break;
					case 2:
						// Same with UVs.
						vertices[elements.back()].uv = uvs[item];
					break;
					default:
						std::cerr << "Unexpected subtoken at index " << j << " with token " << token << " at line " << line << std::endl;
					break;
				}
			} while(pos != std::string::npos, j++);
		}
	}
}

void Material::initialize() {
	glGenBuffers(1, &elements_ibo);
	update_buffers();

	shader->initialize();
}

void Material::update_buffers() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_ibo);
	// Base on https://docs.gl/gl3/glDrawElements
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * elements.size(), &elements[0], GL_STATIC_DRAW);
}

void Material::draw(const mat4& model, const mat4& projection, const mat4& view, float time) {
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

void Object::load_from_stream(std::istream &in) {
	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			vec4 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			v.w = 1.0f;
			vertices.push_back(Vertex{v});
		} else if (line.substr(0, 3) == "vn ") {
			std::istringstream s(line.substr(3));

			vec3 normal;
			s >> normal.x;
			s >> normal.y;
			s >> normal.z;
			
			normals.push_back(normal);
		} else if (line.substr(0, 3) == "vt ") {
			std::istringstream s(line.substr(3));

			vec2 texture;
			s >> texture.x;
			s >> texture.y;

			uv.push_back(texture);
		} else if (line.substr(0, 7) == "usemtl ") {
			materials.insert(materials.begin(), std::make_shared<Material>());
		} else if (line.substr(0, 2) == "f ") {
			if (materials.size() <= 0) {
				materials.insert(materials.begin(), std::make_shared<Material>());
			}

			materials.front()->update_from_element_line(line, vertices, normals, uv);
		}
	}
}

Object::Object(const char* filename) {
	std::ifstream in(filename, std::ios::in);
	if (!in) {
		std::cerr << "Could not load " << filename << std::endl;
		return;
	}
	load_from_stream(in);
	in.close();
}

Object::Object(std::istream &in) {
	load_from_stream(in);
}

Object::~Object() {
	glDeleteBuffers(1, &vertices_vbo);
	for (auto m: materials) {
		m.reset();
	}
}

void Object::initialize() {
	glGenBuffers(1, &vertices_vbo);
	update_buffers();

	for (auto m : materials) {
		m->initialize();
	}
}

void Object::update_buffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// We can delete data after use:
	// TODO: Probably shouldn't use this if we want to dynamically update the buffers.
	normals.clear();
	uv.clear();
	vertices.clear();
}



void Object::draw(const mat4& projection, const mat4& view, float time) {
	
	// Enable drawing position:
	glEnableVertexAttribArray(position_idx);
	glEnableVertexAttribArray(normal_idx);
	glEnableVertexAttribArray(uv_idx);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

	// Connect the current array buffer to the attribute array:
	glVertexAttribPointer(position_idx, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(normal_idx, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec4));
	glVertexAttribPointer(uv_idx, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4) + sizeof(vec3)));

	for (auto m: materials) {
		m->draw(model, projection, view, time);
	}

	glDisableVertexAttribArray(position_idx);
	glDisableVertexAttribArray(normal_idx);
	glDisableVertexAttribArray(uv_idx);
}