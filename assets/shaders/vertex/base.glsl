#version 330 core

import(rand, inVertex, outVertex, uniforms)

void main() {
	float timeOffset = 10 * rand(position.xz);
	float lngth = 0.6f * (0.1f + rand(vec2(rand(position.xy), position.z)) * sin(timeOffset + time/100));
	vec4 newPos = vec4(lngth * position.x, lngth * position.y, lngth * position.z, position.w);
	gl_Position = projection * view * model * newPos;
	vertPos = newPos;
}