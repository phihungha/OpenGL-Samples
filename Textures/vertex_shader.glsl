#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

uniform mat4 transform;

out vec3 vertColor;
out vec2 vertTexCoords;

void main() {
	gl_Position = transform * vec4(pos, 1.0);
	vertColor = color;
	vertTexCoords = texCoords;
}
