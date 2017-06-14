

#include "particle_system.h"

char	init_error(char *str)
{
	printf("%s\n", str);
	glfwTerminate();
	return (0);
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
	// glfwSetKeyCallback(window->win, key_callback);
	return (1);
}
