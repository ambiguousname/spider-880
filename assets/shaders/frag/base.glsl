#version 330 core

out vec4 FragColor;

in vec4 vertPos;

uniform float time;

void main() {
	FragColor = vec4(distance(vertPos.xyz, vec3(0)) * (cos(time/1000) + 0.1f), 0, 0, 1.0f);
}