#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoords;

out vec3 ourColor;
out vec2 TextCoords;

uniform mat4 transf;

void main()
{
	gl_Position = transf * vec4(position, 1.0);
	ourColor = color;
	TextCoords = vec2(textCoords.x, textCoords.y);
}
