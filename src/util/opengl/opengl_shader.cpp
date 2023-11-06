#include "opengl_shader.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdexcept>

Shader::Shader(const char* vertex_file, const char* frag_file) {
	std::ifstream vs;
	if (vertex_file != nullptr) {
		vs.open(vertex_file);
		if (!vs.is_open()) {
			std::cerr << "Could not open vertex shader " << vertex_file << ": " << strerror(errno) << std::endl;
			return;
		}
		vertex_string << vs.rdbuf();
		vs.close();
	}

	std::ifstream fs(frag_file);
	if (frag_file != nullptr) {
		fs.open(frag_file);
		if (!fs.is_open()) {
			std::cerr << "Could not open frag shader " << frag_file << ": " << strerror(errno) << std::endl;
			return;
		}
		frag_string << fs.rdbuf();
		fs.close();
	}
}

void Shader::initialize() {
	if (!initialized) {
		loadFromString(vertex_string.str().c_str(), frag_string.str().c_str());
		initialized = true;
	}
}

void Shader::loadFromString(const char* vertex, const char* frag) {
	int success;
	char infoLog[512];

	const char** vertex_source = &vertex;
	
	int vertex_shader = -1;
	if (vertex_source != nullptr) {
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_source, NULL);
		glCompileShader(vertex_shader);

		glGetProgramiv(program_idx, GL_COMPILE_STATUS, &success);

		if(!success) {
			glGetProgramInfoLog(program_idx, 512, NULL, infoLog);
			std::cerr << "Vertex Shader Program Compiling Failed\n" << infoLog << std::endl;
		}
	}

	const char** frag_source = &frag;

	int frag_shader = -1;
	if (frag_source != nullptr) {
		frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag_shader, 1, frag_source, NULL);
		glCompileShader(frag_shader);
		
		glGetProgramiv(program_idx, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program_idx, 512, NULL, infoLog);
			std::cerr << "Frag Shader Program Compiling Failed\n" << infoLog << std::endl;
		}
	}

	program_idx = glCreateProgram();
	if (frag_shader >= 0) {
		glAttachShader(program_idx, frag_shader);
	}
	if (vertex_shader >= 0) {
		glAttachShader(program_idx, vertex_shader);
	}
	glLinkProgram(program_idx);

	glGetProgramiv(program_idx, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(program_idx, 512, NULL, infoLog);
		std::cerr << "Shader Program Linking Failed\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);
}

const int Shader::getProgram() const {
	if (!initialized) {
		throw std::logic_error("Shader initialize() not called.");
	}
	return program_idx;
}

Shader::~Shader() {
	glDeleteProgram(program_idx);
}