

#include "particle_system.h"

void	update_values_with_keys(void)
{
	if (g_keys[GLFW_KEY_KP_ADD])
		g_zoom_factor *= 1.03;
	if (g_keys[GLFW_KEY_KP_SUBTRACT])
		g_zoom_factor /= 1.03;
	if (g_keys[GLFW_KEY_W])
		g_view_decal_y += 0.05;
	if (g_keys[GLFW_KEY_S])
		g_view_decal_y -= 0.05;
	if (g_keys[GLFW_KEY_D])
		g_view_decal_x -= 0.05;
	if (g_keys[GLFW_KEY_A])
		g_view_decal_x += 0.05;
	if (g_keys[GLFW_KEY_EQUAL])
		g_gravity_strength *= 1.05;
	if (g_keys[GLFW_KEY_MINUS])
		g_gravity_strength /= 1.05;
}