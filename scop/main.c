

#include "myopengl.h"

void	setup_conf()
{
	g_conf.lines = 0;
	g_conf.obj_scale = 1.0;
	g_conf.win_width = 1300;
	g_conf.win_height = 1000;
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

float	max(float f1, float f2)
{
	return (f1 >= f2 ? f1 : f2);
}

void	center_vertices(GLfloat *vertices, int nb_vertices,
														GLfloat x_y_z_mmax[6])
{
	int			i;
	GLfloat		x_diff;
	GLfloat		y_diff;
	GLfloat		z_diff;

	x_diff = (x_y_z_mmax[0] + x_y_z_mmax[1]) / 2.0;
	y_diff = (x_y_z_mmax[2] + x_y_z_mmax[3]) / 2.0;
	z_diff = (x_y_z_mmax[4] + x_y_z_mmax[5]) / 2.0;
	i = 0;
	while (i < nb_vertices)
	{
		vertices[i * 8] -= x_diff;
		vertices[i * 8 + 1] -= y_diff;
		vertices[i * 8 + 2] -= z_diff;
		i++;
	}
}

void	adjust_scale(GLfloat x_y_z_mmax[6])
{
	GLfloat		x_diff;
	GLfloat		y_diff;
	GLfloat		z_diff;
	GLfloat		biggest_diff;

	x_diff = (x_y_z_mmax[0] - x_y_z_mmax[1]);
	y_diff = (x_y_z_mmax[2] - x_y_z_mmax[3]);
	z_diff = (x_y_z_mmax[4] - x_y_z_mmax[5]);
	biggest_diff = max(fabs(x_diff), fabs(y_diff));
	biggest_diff = max(biggest_diff, fabs(z_diff));
	printf("diff : %f\n", biggest_diff);
	g_conf.obj_scale = 3.0 / biggest_diff;
}

void	adjust_obj(GLfloat *vertices, int nb_vertices)
{
	GLfloat		x_y_z_mmax[6];
	int			i;

	i = 0;
	while (i < nb_vertices)
	{
		if (i == 0 || vertices[i * 8] < x_y_z_mmax[0])
			x_y_z_mmax[0] = vertices[i * 8];
		if (i == 0 || vertices[i * 8] > x_y_z_mmax[1])
			x_y_z_mmax[1] = vertices[i * 8];
		if (i == 0 || vertices[i * 8 + 1] < x_y_z_mmax[2])
			x_y_z_mmax[2] = vertices[i * 8 + 1];
		if (i == 0 || vertices[i * 8 + 1] > x_y_z_mmax[3])
			x_y_z_mmax[3] = vertices[i * 8 + 1];
		if (i == 0 || vertices[i * 8 + 2] < x_y_z_mmax[4])
			x_y_z_mmax[4] = vertices[i * 8 + 2];
		if (i == 0 || vertices[i * 8 + 2] > x_y_z_mmax[5])
			x_y_z_mmax[5] = vertices[i * 8 + 2];
		i++;
	}
	center_vertices(vertices, nb_vertices, x_y_z_mmax);
	adjust_scale(x_y_z_mmax);
}

int		main(void)
{
	t_window			*window;
	t_shader_program	*program;
	t_globj				*obj;
	GLfloat				current_frame;
	GLfloat				last_frame;
	GLfloat				delta_time;
	int					attribs_struct[] = {3, 2, 3};
	int					nb_attribs = 3;
	GLfloat				*vertices;
	int					nb_vertices;

	current_frame = 0.0;
	setup_keys();
	setup_conf();
	init_camera();
	window = setup_window(g_conf.win_width, g_conf.win_height, "My window!");
	if (!window)
		return (-1);
	glEnable(GL_DEPTH_TEST);
	program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!program)
		return (-1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	t_objfile	*objfile = parse_objfile("ressources/bunny.obj");
	if (!objfile)
	{
		printf("could not parse .obj\n");
		return (-1);
	}
	if (!(objfile_to_vertices(objfile, &vertices, &nb_vertices)))
	{
		printf("error in .obj\n");
		return (-1);
	}
	adjust_obj(vertices, nb_vertices);
	obj = new_object(vertices, nb_vertices, attribs_struct, nb_attribs);
	if (!obj)
		return (-1);
	//attach_indices_to_obj(obj, indices, nb_indices);
	//load_texture_to_obj(obj, "wooden.jpg");
	//load_texture_to_obj(obj, "awesomeface.png");
	while (!glfwWindowShouldClose(window->win))
	{
		last_frame = current_frame;
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program->program);

		do_movement(delta_time);
		update_camera();

		t_mat	*model;
		t_mat	*view;
		t_mat	*projection;
		t_mat	*scal;

		scal = scale(new_vec3(g_conf.obj_scale, g_conf.obj_scale, g_conf.obj_scale));
		model = rotate(new_vec3(0.0, 0.0, deg_to_rad((GLfloat)glfwGetTime() * 15.0f)));
		model = mat_mult(model, scal);
		//view = translate(new_vec3(0.0, 0.0, -3.0 + (mixVal * 4)));
		//model = new_mat4();
		view = build_view();
		projection = perspective(deg_to_rad(g_cam.fov), ((float)g_conf.win_height) / g_conf.win_width, 0.1, 100.0);

		GLuint	loc1 = glGetUniformLocation(program->program, "model");
		glUniformMatrix4fv(loc1, 1, GL_TRUE, model->elts);

		GLuint	loc2 = glGetUniformLocation(program->program, "view");
		glUniformMatrix4fv(loc2, 1, GL_TRUE, view->elts);

		GLuint	loc3 = glGetUniformLocation(program->program, "projection");
		glUniformMatrix4fv(loc3, 1, GL_TRUE, projection->elts);

		draw_object(program, obj);

		glfwSwapBuffers(window->win);
	}
	glfwTerminate();
	return (0);
}
