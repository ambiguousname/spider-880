#include "opengl_obj.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

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

			texcoords.push_back(texture);
		} else if (line.substr(0, 7) == "usemtl ") {
			geometries.insert(geometries.begin(), std::make_shared<ObjectGeometry>());
		} else if (line.substr(0, 2) == "f ") {
			if (geometries.size() <= 0) {
				geometries.insert(geometries.begin(), std::make_shared<ObjectGeometry>());
			}

			geometries.front()->update_from_element_line(line, vertices, normals, texcoords);
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
	for (auto g: geometries) {
		g.reset();
	}
}

void Object::initialize() {
	glGenBuffers(1, &vertices_vbo);
	update_buffers();

	for (auto g : geometries) {
		g->initialize();
	}
}

void Object::update_buffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// We can delete data after use:
	// TODO: Probably shouldn't use this if we want to dynamically update the buffers.
	normals.clear();
	texcoords.clear();
	vertices.clear();
}



void Object::draw(const mat4& projection, const mat4& view, float time) {
	
	// Enable drawing position:
	glEnableVertexAttribArray(position_idx);
	glEnableVertexAttribArray(normal_idx);
	glEnableVertexAttribArray(texcoord_idx);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

	// Connect the current array buffer to the attribute array:
	glVertexAttribPointer(position_idx, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(normal_idx, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec4));
	glVertexAttribPointer(texcoord_idx, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4) + sizeof(vec3)));

	for (auto g: geometries) {
		g->draw(model, projection, view, time);
	}

	glDisableVertexAttribArray(position_idx);
	glDisableVertexAttribArray(normal_idx);
	glDisableVertexAttribArray(texcoord_idx);
}