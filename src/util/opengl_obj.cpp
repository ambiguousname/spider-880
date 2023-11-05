#include "opengl_obj.h"
#include <fstream>
#include <sstream>

// Modified from https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
void Object::loadFromStream(std::istream &in) {
	std::string line;
	while (getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			vec4 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			v.w = 1.0f;
			vertices.push_back(v);
		} else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			GLushort a,b,c;
			s >> a;
			s >> b;
			s >> c;
			a--; b--; c--;
			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
		}
	}

	normals.resize(vertices.size(), vec3(0, 0, 0));
	for (int i = 0; i < elements.size(); i+= 3) {
		GLushort ia = elements[i];
        GLushort ib = elements[i+1];
        GLushort ic = elements[i+2];
        glm::vec3 normal = glm::normalize(glm::cross(glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]), glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        normals[ia] = normals[ib] = normals[ic] = normal;
	}
}

Object::Object(const char* filename) {
	std::ifstream in(filename, std::ios::in);
	if (!in) {
		std::cerr << "Could not load " << filename << std::endl;
		return;
	}
	loadFromStream(in);
}

Object::Object(std::istream &in) {
	loadFromStream(in);
}

Object::~Object() {
	glDeleteBuffers(1, &vertices_vbo);
}

void Object::initialize() {
	glGenBuffers(1, &vertices_vbo);
	glGenBuffers(1, &elements_ibo);
	update_buffers();
}

void Object::update_buffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	// Set to DYNAMIC_DRAW in case we want to update our vertices:
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size(), &elements[0], GL_STATIC_DRAW);
}

void Object::draw() {
	// Load vertices and index of vertices:
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_ibo);

	glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, NULL);
}