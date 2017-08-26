#version 410 core

layout (location = 0) out vec3 color;

in vec2 RawCoords;
in vec2 Coords;

uniform float zoom_factor;
uniform float view_decal_x;
uniform float view_decal_y;
uniform float mouse_position_x;
uniform float mouse_position_y;
uniform float time;

void	main()
{
	float x_diff = RawCoords.x - (mouse_position_x / zoom_factor - (view_decal_x / zoom_factor));
	float y_diff = RawCoords.y - (mouse_position_y / zoom_factor + (view_decal_y / zoom_factor));
	float distance_mouse = sqrt((x_diff * x_diff) + (y_diff * y_diff));
	/*if (distance_mouse > 3.0)
		distance_mouse = 3.0;
	distance_mouse = -(distance_mouse - 3.0);
	distance_mouse /= 3.0;*/
	if (distance_mouse < 0.4)
		distance_mouse = 0.4;
	if (distance_mouse > 4.0)
		distance_mouse = 4.0;
	distance_mouse = 1.0 / distance_mouse;
	int color_time = int(time * 10) % 200;
	if (color_time > 100)
		color_time = 100 - (color_time - 100);
	color_time += 20;
	float color_time_influence = float(color_time / 120.0);
	color_time_influence;
	float r = color_time_influence;
	float g = 1.0 - color_time_influence;
	float b = 0.3;
	r *= distance_mouse;
	g *= distance_mouse;
	b *= distance_mouse;
	color = vec3(r, g, b);
}