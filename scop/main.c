
#include "myopengl.h"

GLfloat vertices[] = {
    // Positions          // Colors           // Texture Coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left 
};
int		attribs_struct[] = {3, 3, 2};
int		nb_attribs = 3;
int		nb_vertices = 4;

GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3    // Second Triangle
};
int		nb_indices = 6;

/*
GLint		loc = glGetUniformLocation(program->program, "alpha");
glUseProgram(program->program);
glUniform1f(loc, alpha);
*/

int		main(void)
{
	t_window			*window;
	t_shader_program	*program;
	t_globj				*obj;

	window = setup_window(1200, 900, "My window!");
	if (!window)
		return (-1);
	program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!program)
		return (-1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	obj = new_object(vertices, attribs_struct, nb_attribs, nb_vertices);
	if (!obj)
		return (-1);
	attach_indices_to_obj(obj, indices, nb_indices);
	load_texture_to_obj(obj, "container.jpg");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window->win))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		draw_object(program, obj);

		glfwSwapBuffers(window->win);
	}
	glfwTerminate();
	return (0);
}
