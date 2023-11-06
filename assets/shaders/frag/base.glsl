#version 330 core

out vec4 FragColor;

in vec4 vertPos;

uniform float time;

void main() {
	FragColor = vec4(distance(vertPos.xyz, vec3(0)), sin(time/50), sin(time/50), 1.0f);
}