

#include "particle_system.h"

char	init_error(char *str)
{
	printf("%s\n", str);
	glfwTerminate();
	return (0);
}

void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	(void)scancode;
	(void)mode;
	if (action == GLFW_PRESS)
		g_keys[key] = 1;
	if (action == GLFW_RELEASE)
		g_keys[key] = 0;
	if (action != GLFW_PRESS)
		return ;
	if (key == GLFW_KEY_L)
	{
		if (g_center_gravity_lock)
			g_center_gravity_lock = 0;
		else
			g_center_gravity_lock = 1;
	}
	if (key == GLFW_KEY_G)
	{
		if (g_center_gravity_activated)
			g_center_gravity_activated = 0;
		else
			g_center_gravity_activated = 1;
	}
	if (key == GLFW_KEY_P)
	{
		if (g_particles_locked)
			g_particles_locked = 0;
		else
			g_particles_locked = 1;
	}
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static void	mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	if (!g_center_gravity_lock)
	{
		g_center_gravity_x = (((float)xpos) / g_screen_width) * 2.0 - 1.0;
		g_center_gravity_y = -((((float)ypos) / g_screen_height) * 2.0 - 1.0);
		g_center_gravity_x -= g_view_decal_x;
		g_center_gravity_y += g_view_decal_y;
		g_center_gravity_x /= g_zoom_factor;
		g_center_gravity_y /= g_zoom_factor;
		g_center_gravity_x = g_center_gravity_x * g_screen_width / g_screen_height;
	}
	g_mouse_position_x = (((float)xpos) / g_screen_width) * 2.0 - 1.0;
	g_mouse_position_y = -((((float)ypos) / g_screen_height) * 2.0 - 1.0);
}

char	setup_window(int width, int height, char *title_name, t_window *window)
{
	int			actual_width;
	int			actual_height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window->win = glfwCreateWindow(width, height, title_name, NULL, NULL);
	if (!window->win)
		return (init_error("Failed to create GLFW window\n"));
	glfwMakeContextCurrent(window->win);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return (init_error("Failed to initialize GLEW\n"));
	glfwGetFramebufferSize(window->win, &actual_width, &actual_height);
	glViewport(0, 0, actual_width, actual_height);
	glfwSetKeyCallback(window->win, key_callback);
	glfwSetCursorPosCallback(window->win, mouse_callback);
	return (1);
}
