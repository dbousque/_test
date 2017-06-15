#version 410 core

layout (location = 0) in vec2 coords;

out vec2 Coords;

void main()
{
	gl_Position = vec4(coords.x, coords.y, 0.0, 1.0);
	Coords = coords;
}
