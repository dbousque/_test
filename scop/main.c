
#include "myopengl.h"

GLfloat		vertices3[] = {
	-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f,  -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f
};
int		attribs_struct3[] = {3, 3};
int		nb_attribs3 = 2;
int		nb_vertices3 = 3;

int		main(void)
{
	t_window			*window;
	t_shader_program	*program;
	t_globj				*obj;

	window = setup_window(1600, 1200, "My window!");
	if (!window)
		return (-1);
	program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!program)
		return (-1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	obj = new_object(vertices3, attribs_struct3, nb_attribs3, nb_vertices3);
	if (!obj)
		return (-1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window->win))
	{
		glfwPollEvents();

		glClearColor(0.01f, 0.0f, 0.20f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat		time = glfwGetTime();
		GLfloat		alpha = (sin(time * 4) / 2) + 0.5;
		GLint		loc = glGetUniformLocation(program->program, "alpha");
		GLint		loc2 = glGetUniformLocation(program->program, "offset");
		glUseProgram(program->program);
		glUniform1f(loc, alpha);
		glUniform1f(loc2, alpha);

		draw_object(program, obj);
		glfwSwapBuffers(window->win);
	}
	glfwTerminate();
	return (0);
}
