#version 410 core

layout (location = 0) in float mass;
layout (location = 1) in vec2 coords;
layout (location = 2) in vec2 velocity;

out vec2 Coords;

void main()
{
	gl_Position = vec4(coords.x, coords.y, 0.0, 1.0);
	Coords = coords;
}
