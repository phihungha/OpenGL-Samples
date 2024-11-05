#version 330 core

uniform float mixAmount;
uniform sampler2D tex1;
uniform sampler2D tex2;

in vec3 vertColor;
in vec2 vertTexCoords;

out vec4 fragColor;

void main() {
	fragColor = mix(
		texture(tex1, vertTexCoords), 
		texture(tex2, vec2(1.0 - vertTexCoords.x, vertTexCoords.y)), 
		mixAmount);
}
