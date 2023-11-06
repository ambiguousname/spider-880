#version 330 core

out vec4 FragColor;

in vec4 vertColor;

void main() {
	FragColor = vec4(vertColor.x, vertColor.y, 1.0f, 1.0f);
}