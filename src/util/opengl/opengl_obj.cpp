#include "opengl_obj.h"
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

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
			v.x *= 100;
			v.y *= 100;

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
        vec3 normal = normalize(cross(vec3(vertices[ib]) - vec3(vertices[ia]), vec3(vertices[ic]) - vec3(vertices[ia])));
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
	in.close();
}

Object::Object(std::istream &in) {
	loadFromStream(in);
}

Object::~Object() {
	glDeleteBuffers(1, &vertices_vbo);
}

void Object::initialize() {
	glGenVertexArrays(1, &attributes_vao);
	glGenBuffers(1, &vertices_vbo);
	glGenBuffers(1, &elements_ibo);
	update_buffers();

	// position_idx = glGetAttribLocation();
}

void Object::update_buffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4) * vertices.size(), &vertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * elements.size(), &elements[0], GL_STATIC_DRAW);

	// Set position:
	
	// glBindVertexArray(attributes_vao);
	// glVertexAttribPointer(, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), (void*)0);
	// glBindVertexArray(0);
}



void Object::draw() {
	// Enable drawing position:
	glEnableVertexAttribArray(position_idx);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

	// Connect the current array buffer to the attribute array:
	glVertexAttribPointer(position_idx, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glUniformMatrix4fv(transform_idx, 1, GL_FALSE, glm::value_ptr(transform));

	// Prepare to draw elements:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_ibo);
	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_SHORT, (void*)0);

	
	glDisableVertexAttribArray(position_idx);
}