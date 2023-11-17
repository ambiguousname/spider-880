#pragma once
#include "gl.h"
#include <sstream>
#include <glm/glm.hpp>

using namespace glm;

class Shader {
	protected:
	int program_idx;
	
	int model_idx;
	int projection_idx;
	int view_idx;
	int time_idx;

	void loadFromString(const char* vertex, const char* frag);

	std::stringstream frag_string;
	std::stringstream vertex_string;

	bool initialized = false;

	public:
	Shader(const char* vertex_file=nullptr, const char* frag_file=nullptr);
	~Shader();

	void useProgram();
	void setAttrs(const f32* model_ptr, const f32* projection_ptr, const f32* view_ptr, float time=0);

	int getProgram() const;
	void initialize();
};