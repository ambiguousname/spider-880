#version 330 core

layout (location=0) in vec4 position;

out vec4 vertPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

// Pseudo-random:
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
	float lngth = 0.6f * (0.1f + rand(vec2(rand(position.xy), position.z)) * sin(time/100));
	vec4 newPos = vec4(lngth * position.x, lngth * position.y, lngth * position.z, position.w);
	gl_Position = projection * view * model * newPos;
	vertPos = newPos;
}