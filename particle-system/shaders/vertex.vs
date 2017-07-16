#version 410 core

layout (location = 0) in float mass;
layout (location = 1) in vec2 coords;
layout (location = 2) in vec2 velocity;

out vec2 RawCoords;
out vec2 Coords;

uniform float screen_ratio;
uniform float zoom_factor;
uniform float view_decal_x;
uniform float view_decal_y;

void main()
{
	RawCoords = coords;
	float x = coords.x / screen_ratio * zoom_factor + view_decal_x;
	float y = coords.y * zoom_factor - view_decal_y;
	gl_Position = vec4(x, y, 0.0, 1.0);
	Coords = coords;
}
