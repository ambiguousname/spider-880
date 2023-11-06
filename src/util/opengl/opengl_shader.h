#pragma once
#include "gl.h"

class Shader {
	int program_idx;

	char* vertex_program;	
	char* frag_program;

	public:
	Shader(const char* vertex=nullptr, const char* frag=nullptr);

	int getProgram() { return program_idx; }
};