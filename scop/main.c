

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

void	front_up_cross(float *x, float *y, float *z)
{
	*x = (g_cam.front_y * g_cam.up_z) - (g_cam.front_z * g_cam.up_y);
	*y = (g_cam.front_z * g_cam.up_x) - (g_cam.front_x * g_cam.up_z);
	*z = (g_cam.front_x * g_cam.up_y) - (g_cam.front_y * g_cam.up_x);
}

void    key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	(void)window;
	(void)scancode;
	(void)action;
	(void)mode;
	int		norm;
	float	tmp_x;
	float	tmp_y;
	float	tmp_z;

	printf("key : %d, action : %d\n", key, action);
	//if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))

	if (key == GLFW_KEY_W)
	{
		g_cam.x += g_cam.speed * g_cam.front_x;
		g_cam.y += g_cam.speed * g_cam.front_y;
		g_cam.z += g_cam.speed * g_cam.front_z;
	}
	if (key == GLFW_KEY_S)
	{
		g_cam.x -= g_cam.speed * g_cam.front_x;
		g_cam.y -= g_cam.speed * g_cam.front_y;
		g_cam.z -= g_cam.speed * g_cam.front_z;
	}
	if (key == GLFW_KEY_A)
	{
		front_up_cross(&tmp_x, &tmp_y, &tmp_z);
		norm = get_norm(tmp_x, tmp_y, tmp_z);
		g_cam.x -= tmp_x / norm * g_cam.speed;
		g_cam.y -= tmp_y / norm * g_cam.speed;
		g_cam.z -= tmp_z / norm * g_cam.speed;
	}
	if (key == GLFW_KEY_D)
	{
		front_up_cross(&tmp_x, &tmp_y, &tmp_z);
		norm = get_norm(tmp_x, tmp_y, tmp_z);
		g_cam.x += tmp_x / norm * g_cam.speed;
		g_cam.y += tmp_y / norm * g_cam.speed;
		g_cam.z += tmp_z / norm * g_cam.speed;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void	init_camera(void)
{
	g_cam.x = 0.0;
	g_cam.y = 0.0;
	g_cam.z = 3.0;
	g_cam.front_x = 0.0;
	g_cam.front_y = 0.0;
	g_cam.front_z = -1.0;
	g_cam.up_x = 0.0;
	g_cam.up_y = 1.0;
	g_cam.up_z = 0.0;
	g_cam.speed = 0.05;
	g_cam.fov = 200.0;
}

t_mat	*build_view(void)
{
	t_vec	*camera_pos;
	t_vec	*camera_target;
	t_vec	*camera_direction;
	t_vec	*up;
	t_vec	*camera_right;
	t_vec	*camera_up;
	t_mat	*tmp1;
	t_mat	*tmp2;

	camera_pos = new_vec3(g_cam.x, g_cam.y, g_cam.z);
	camera_target = new_vec3(g_cam.x + g_cam.front_x, g_cam.y + g_cam.front_y,
														g_cam.z + g_cam.front_z);
	camera_direction = vec3_normalize(vec3_sub(camera_pos, camera_target));
	up = new_vec3(g_cam.up_x, g_cam.up_y, g_cam.up_z);
	camera_right = vec3_normalize(vec3_cross(up, camera_direction));
	camera_up = vec3_cross(camera_direction, camera_right);
	tmp1 = new_mat4();
	tmp1->elts[0] = camera_right->elts[0];
	tmp1->elts[1] = camera_right->elts[1];
	tmp1->elts[2] = camera_right->elts[2];
	tmp1->elts[4] = camera_up->elts[0];
	tmp1->elts[5] = camera_up->elts[1];
	tmp1->elts[6] = camera_up->elts[2];
	tmp1->elts[8] = camera_direction->elts[0];
	tmp1->elts[9] = camera_direction->elts[1];
	tmp1->elts[10] = camera_direction->elts[2];
	tmp2 = new_mat4();
	tmp2->elts[3] = -(camera_pos->elts[0]);
	tmp2->elts[7] = -(camera_pos->elts[1]);
	tmp2->elts[11] = -(camera_pos->elts[2]);
	return (mat_mult(tmp1, tmp2));
}

int		main(void)
{
	t_window			*window;
	t_shader_program	*program;
	t_globj				*obj;
	int					i;

	setup_cube_positions();
	init_camera();
	window = setup_window(1000, 800, "My window!");
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
		//glUniform1f(glGetUniformLocation(program->program, "mixVal"), mixVal);

		t_mat	*model;
		t_mat	*view;
		t_mat	*projection;
		t_mat	*rot;

		//model = rotate(new_vec3(0.0, deg_to_rad((GLfloat)glfwGetTime() * 25.0f), deg_to_rad((GLfloat)glfwGetTime() * 50.0f)));
		//view = translate(new_vec3(0.0, 0.0, -3.0 + (mixVal * 4)));
		view = build_view();
		projection = perspective(g_cam.fov, 800.0 / 1000.0, 0.1, 100.0);

		GLuint	loc2 = glGetUniformLocation(program->program, "view");
		glUniformMatrix4fv(loc2, 1, GL_TRUE, view->elts);

		GLuint	loc3 = glGetUniformLocation(program->program, "projection");
		glUniformMatrix4fv(loc3, 1, GL_TRUE, projection->elts);

		i = 0;
		while (i < nb_cubes)
		{
			model = translate(cubePositions[i]);
			rot = rotate(new_vec3(0.0, i * 5.0, i % 3 == 0 ? (i + 0.0) * glfwGetTime() : i * 20.0));
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