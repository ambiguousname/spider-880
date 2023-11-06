#pragma once
#include "gl.h"

class Shader {
	int program_idx;

	public:
	Shader(const char* vertex=nullptr, const char* frag=nullptr);

	int getProgram() { return program_idx; }
};