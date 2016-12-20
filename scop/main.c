

#include "myopengl.h"

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
int		attribs_struct[] = {3, 2};
int		nb_attribs = 2;
int		nb_vertices = 36;

t_vec *cubePositions[10];
int		nb_cubes = 10;

void	setup_cube_positions()
{
	cubePositions[0] = new_vec3( 0.0f,  0.0f,  0.0f);
	cubePositions[1] = new_vec3( 2.0f,  5.0f, -15.0f);
	cubePositions[2] = new_vec3(-1.5f, -2.2f, -2.5f);
	cubePositions[3] = new_vec3(-3.8f, -2.0f, -12.3f);
	cubePositions[4] = new_vec3( 2.4f, -0.4f, -3.5f);
	cubePositions[5] = new_vec3(-1.7f,  3.0f, -7.5f);
	cubePositions[6] = new_vec3( 1.3f, -2.0f, -2.5f);
	cubePositions[7] = new_vec3( 1.5f,  2.0f, -2.5f);
	cubePositions[8] = new_vec3( 1.5f,  0.2f, -1.5f);
	cubePositions[9] = new_vec3(-1.3f,  1.0f, -1.5f);
}

/*GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3,   // First Triangle
    1, 2, 3,   // Second Triangle

    4, 5, 7,   // First Triangle
    5, 6, 7,    // Second Triangle

    8, 9, 10,
    9, 10, 11
};
int		nb_indices = 18;*/

/*
GLint		loc = glGetUniformLocation(program->program, "alpha");
glUseProgram(program->program);
glUniform1f(loc, alpha);
*/

float	mixVal = 0.2;

void    key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	(void)window;
	(void)scancode;
	(void)action;
	(void)mode;
	printf("key : %d, action : %d\n", key, action);
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		mixVal += 0.05;
		if (mixVal > 1.0)
			mixVal = 1.0;
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		mixVal -= 0.05;
		if (mixVal < 0.0)
			mixVal = 0.0;
	}
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int		main(void)
{
	t_window			*window;
	t_shader_program	*program;
	t_globj				*obj;
	int					i;

	setup_cube_positions();
	window = setup_window(1200, 900, "My window!");
	if (!window)
		return (-1);
	glEnable(GL_DEPTH_TEST);
	program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!program)
		return (-1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	obj = new_object(vertices, attribs_struct, nb_attribs, nb_vertices);
	if (!obj)
		return (-1);
	//attach_indices_to_obj(obj, indices, nb_indices);
	load_texture_to_obj(obj, "container.jpg");
	load_texture_to_obj(obj, "awesomeface.png");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window->win))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program->program);
		glUniform1f(glGetUniformLocation(program->program, "mixVal"), mixVal);

		t_mat	*model;
		t_mat	*view;
		t_mat	*projection;
		t_mat	*rot;

		//model = rotate(new_vec3(0.0, deg_to_rad((GLfloat)glfwGetTime() * 25.0f), deg_to_rad((GLfloat)glfwGetTime() * 50.0f)));
		view = translate(new_vec3(0.0, 0.0, -3.0 + (mixVal * 4)));
		projection = perspective(0.0, 900.0 / 1200.0, 0.1, 100.0);

		GLuint	loc2 = glGetUniformLocation(program->program, "view");
		glUniformMatrix4fv(loc2, 1, GL_TRUE, view->elts);

		GLuint	loc3 = glGetUniformLocation(program->program, "projection");
		glUniformMatrix4fv(loc3, 1, GL_TRUE, projection->elts);

		i = 0;
		while (i < nb_cubes)
		{
			model = translate(cubePositions[i]);
			rot = rotate(new_vec3(0.0, i * 5.0, i % 3 == 0 ? i * glfwGetTime() : i * 20.0));
			model = mat_mult(model, rot);
			GLuint	loc = glGetUniformLocation(program->program, "model");
			glUniformMatrix4fv(loc, 1, GL_TRUE, model->elts);

			draw_object(program, obj);
			i++;
		}

		glfwSwapBuffers(window->win);
	}
	glfwTerminate();
	return (0);
}
