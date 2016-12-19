#version 330 core

in vec2 TextCoords;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform float mixVal;

void main()
{
	color = mix(texture(ourTexture1, TextCoords), texture(ourTexture2, TextCoords), 1.0 - mixVal);
}
