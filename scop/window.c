

#include "myopengl.h"

t_window	*init_error(char *str)
{
	ft_putstr(str);
	glfwTerminate();
	return (NULL);
}

t_window	*setup_window(int width, int height, char *title_name)
{
	t_window	*window;
	int			actual_width;
	int			actual_height;

	if (!(window = (t_window*)malloc(sizeof(t_window))))
	{
		ft_putstr("malloc error\n");
		return (NULL);
	}
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// macos
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
	return (window);
}