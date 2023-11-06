#include "opengl_shader.h"
#include <iostream>
#include <string.h>

Shader::Shader(const char* vertex, const char* frag) {
	int success;
	char infoLog[512];

	const char** vertex_source = &vertex;
	
	int vertex_shader = -1;
	if (vertex_source != nullptr) {
		int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
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
	glAttachShader(program_idx, frag_shader);
	glAttachShader(program_idx, vertex_shader);
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