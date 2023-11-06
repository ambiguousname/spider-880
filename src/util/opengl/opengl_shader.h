#pragma once
#include "gl.h"

class Shader {
	protected:
	int program_idx;

	void loadFromString(const char* vertex, const char* frag);

	public:
	Shader(const char* vertex_file=nullptr, const char* frag_file=nullptr);
	~Shader();

	int getProgram() { return program_idx; }
};