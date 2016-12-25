

#include "myopengl.h"

void	setup_conf()
{
	g_conf.lines = 0;
	g_conf.obj_scale = 1.0;
	g_conf.win_width = 1300;
	g_conf.win_height = 1000;
	g_conf.obj_ind = 0;
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

t_light		*new_std_light(float r, float g, float b)
{
	t_light		*light;
	GLfloat		vertices[] = {
		-0.05, -0.05, 0.05,  r, g, b,
		-0.05,  0.05, 0.05,  r, g, b,
		 0.05, -0.05, 0.05,  r, g, b,
		-0.05,  0.05, 0.05,  r, g, b,
		 0.05, -0.05, 0.05,  r, g, b,
		 0.05,  0.05, 0.05,  r, g, b,

		-0.05, -0.05, -0.05,  r, g, b,
		-0.05,  0.05, -0.05,  r, g, b,
		 0.05, -0.05, -0.05,  r, g, b,
		-0.05,  0.05, -0.05,  r, g, b,
		 0.05, -0.05, -0.05,  r, g, b,
		 0.05,  0.05, -0.05,  r, g, b,

		 0.05, -0.05, -0.05,  r, g, b,
		 0.05,  0.05, -0.05,  r, g, b,
		 0.05, -0.05,  0.05,  r, g, b,
		 0.05,  0.05, -0.05,  r, g, b,
		 0.05, -0.05,  0.05,  r, g, b,
		 0.05,  0.05,  0.05,  r, g, b,

		-0.05, -0.05, -0.05,  r, g, b,
		-0.05,  0.05, -0.05,  r, g, b,
		-0.05, -0.05,  0.05,  r, g, b,
		-0.05,  0.05, -0.05,  r, g, b,
		-0.05, -0.05,  0.05,  r, g, b,
		-0.05,  0.05,  0.05,  r, g, b,

		-0.05,  0.05, -0.05,  r, g, b,
		 0.05,  0.05, -0.05,  r, g, b,
		-0.05,  0.05,  0.05,  r, g, b,
		 0.05,  0.05, -0.05,  r, g, b,
		-0.05,  0.05,  0.05,  r, g, b,
		 0.05,  0.05,  0.05,  r, g, b,

		-0.05, -0.05, -0.05,  r, g, b,
		 0.05, -0.05, -0.05,  r, g, b,
		-0.05, -0.05,  0.05,  r, g, b,
		 0.05, -0.05, -0.05,  r, g, b,
		-0.05, -0.05,  0.05,  r, g, b,
		 0.05, -0.05,  0.05,  r, g, b,
	};
	int			nb_vertices = 36;
	int			attribs_struct[] = {3, 3};
	int			nb_attribs = 2;

	if (!(light = (t_light*)malloc(sizeof(t_light))))
		return (NULL);
	if (!(light->obj = new_object(vertices, nb_vertices, attribs_struct, nb_attribs)))
		return (NULL);
	light->r = r;
	light->g = g;
	light->b = b;
	return (light);
}

void	set_lights(t_list *objs, t_list *lights, t_vec *ambient_color)
{
	size_t		i;
	size_t		x;
	t_globj		*obj;
	t_light		*light;
	GLint		loc;
	char		*tmp;
	char		*x_str;

	i = 0;
	while (i < objs->len)
	{
		obj = ((t_globj**)objs->elts)[i];
		glUseProgram(obj->shader->program);
		loc = glGetUniformLocation(obj->shader->program, "ambientColor");
		glUniform3f(loc, ambient_color->elts[0], ambient_color->elts[1], ambient_color->elts[2]);
		x = 0;
		while (x < lights->len)
		{
			light = ((t_light**)lights->elts)[x];
			x_str = ft_itoa(x + 1);
			tmp = ft_strconcat("lightColor", x_str);
			loc = glGetUniformLocation(obj->shader->program, tmp);
			glUniform3f(loc, light->r, light->g, light->b);
			free(tmp);
			tmp = ft_strconcat("lightPos", x_str);
			loc = glGetUniformLocation(obj->shader->program, tmp);
			glUniform3f(loc, light->obj->x, light->obj->y, light->obj->z);
			free(tmp);
			free(x_str);
			x++;
		}
		i++;
	}
}

void	draw_objects(t_list *objs, t_mat *view, t_mat *projection)
{
	size_t				i;
	t_mat				*model;
	t_mat				*scal;
	t_mat				*trans;
	t_shader_program	*shader;
	GLuint				loc;
	t_globj				*obj;

	i = 0;
	while (i < objs->len)
	{
		obj = ((t_globj**)objs->elts)[i];
		shader = obj->shader;
		glUseProgram(shader->program);
		if (i == 0)
		{
			trans = translate(new_vec3(obj->x, obj->y, obj->z));
			scal = scale(new_vec3(g_conf.obj_scale, g_conf.obj_scale, g_conf.obj_scale));
			model = rotate(new_vec3(0.0, 0.0, deg_to_rad((GLfloat)glfwGetTime() * 15.0f)));
			model = mat_mult(model, scal);
			model = mat_mult(model, trans);
		}
		else
			model = translate(new_vec3(obj->x, obj->y, obj->z));
		//view = translate(new_vec3(0.0, 0.0, -3.0 + (mixVal * 4)));
		//model = new_mat4();
		loc = glGetUniformLocation(shader->program, "model");
		glUniformMatrix4fv(loc, 1, GL_TRUE, model->elts);
		loc = glGetUniformLocation(shader->program, "view");
		glUniformMatrix4fv(loc, 1, GL_TRUE, view->elts);
		loc = glGetUniformLocation(shader->program, "projection");
		glUniformMatrix4fv(loc, 1, GL_TRUE, projection->elts);
		draw_object(shader, ((t_globj**)objs->elts)[i]);
		i++;
	}
}

void	draw_lights(t_list *lights, t_mat *view, t_mat *projection)
{
	size_t				i;
	t_shader_program	*shader;
	GLuint				loc;
	t_light				*light;
	t_mat				*model;

	i = 0;
	while (i < lights->len)
	{
		light = ((t_light**)lights->elts)[i];
		shader = light->obj->shader;

		glUseProgram(shader->program);

		model = translate(new_vec3(light->obj->x, light->obj->y, light->obj->z));

		loc = glGetUniformLocation(shader->program, "model");
		glUniformMatrix4fv(loc, 1, GL_TRUE, model->elts);

		loc = glGetUniformLocation(shader->program, "view");
		glUniformMatrix4fv(loc, 1, GL_TRUE, view->elts);

		loc = glGetUniformLocation(shader->program, "projection");
		glUniformMatrix4fv(loc, 1, GL_TRUE, projection->elts);

		draw_object(shader, light->obj);
		i++;
	}
}

int		main(void)
{
	t_window			*window;
	t_shader_program	*program;
	t_shader_program	*light_program;
	t_globj				*obj;
	t_light				*light;
	GLfloat				current_frame;
	GLfloat				last_frame;
	GLfloat				delta_time;
	int					attribs_struct[] = {3, 2, 3};
	int					nb_attribs = 3;
	GLfloat				*vertices;
	int					nb_vertices;
	t_list				*objs;
	t_list				*lights;
	t_mat				*view;
	t_mat				*projection;

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
	light_program = new_shader_program("shaders/light.vs", "shaders/light.fs");
	if (!light_program)
		return (-1);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	objs = new_list(sizeof(t_globj*));
	lights = new_list(sizeof(t_light*));
	t_objfile	*objfile = parse_objfile("ressources/plane/Su-27_Flanker.obj");
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
	add_to_list(objs, &obj);
	light = new_std_light(1.0, 1.0, 1.0);
	if (!light)
		return (-1);
	add_to_list(lights, &light);
	attach_shader_program_to_obj(obj, program);
	attach_shader_program_to_obj(light->obj, light_program);
	//attach_indices_to_obj(obj, indices, nb_indices);
	//load_texture_to_obj(obj, "wooden.jpg");
	//load_texture_to_obj(obj, "awesomeface.png");
	while (!glfwWindowShouldClose(window->win))
	{
		last_frame = current_frame;
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		glfwPollEvents();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		do_movement(delta_time, objs, lights);
		update_camera();

		view = build_view();
		projection = perspective(deg_to_rad(g_cam.fov), ((float)g_conf.win_height) / g_conf.win_width, 0.1, 100.0);

		set_lights(objs, lights, new_vec3(0.1, 0.1, 0.1));

		draw_objects(objs, view, projection);

		draw_lights(lights, view, projection);

		glfwSwapBuffers(window->win);
	}
	glfwTerminate();
	return (0);
}
