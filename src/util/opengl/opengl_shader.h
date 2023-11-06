#pragma once
#include "gl.h"
#include <sstream>

class Shader {
	protected:
	int program_idx;

	void loadFromString(const char* vertex, const char* frag);

	std::stringstream frag_string;
	std::stringstream vertex_string;

	bool initialized = false;

	public:
	Shader(const char* vertex_file=nullptr, const char* frag_file=nullptr);
	~Shader();

	const int getProgram() const;
	void initialize();
};