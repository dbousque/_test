#version 330 core

in vec3 ourColor;
in vec2 TextCoords;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform float mixVal;

void main()
{
	vec2 Text2Coords = vec2(TextCoords.x, 1.0 - TextCoords.y);
	color = mix(texture(ourTexture2, TextCoords), texture(ourTexture1, Text2Coords), mixVal);
}
