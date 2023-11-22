#version 330 core

import(inFrag, outFrag, uniforms)

void main() {
	FragColor = vec4(distance(vertPos.xyz, vec3(0)), sin(time/50), sin(time/50), 1.0f);
}