#version 330 core

in vec2 TextCoords;
in vec3 NormalVec;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	color = vec4(0.8, 0.8, 0.8, 1.0);
	//color = mix(texture(ourTexture1, TextCoords), texture(ourTexture2, TextCoords), 1.0);
}
