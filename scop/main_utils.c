

#include "myopengl.h"

void	setup_conf(void)
{
	g_conf.lines = 0;
	g_conf.obj_scale = 1.0;
	g_conf.win_width = 1300;
	g_conf.win_height = 1000;
	g_conf.obj_ind = 0;
	g_conf.normal_mode = 0;
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

t_globj		*new_obj_from_path(char *path)
{
	t_objfile	*objfile;
	int			attribs_struct[] = {3, 2, 3};
	int			nb_attribs = 3;
	GLfloat		*vertices;
	int			nb_vertices;

	objfile = parse_objfile(path);
	if (!objfile)
	{
		printf("could not parse .obj\n");
		return (NULL);
	}
	if (!(objfile_to_vertices(objfile, &vertices, &nb_vertices)))
	{
		printf("error in .obj\n");
		return (NULL);
	}
	adjust_obj(vertices, nb_vertices);
	return (new_object(vertices, nb_vertices, attribs_struct, nb_attribs));
}

void	update_stats(void)
{
	g_conf.frames_seen++;
	if (glfwGetTime() - g_conf.info_updated_at >= 2.0)
	{
		printf("fps : %.1f\n", g_conf.frames_seen / g_conf.time_spent);
		printf("time per frame : %.1f ms\n",
							g_conf.time_spent / g_conf.frames_seen * 1000.0);
		g_conf.frames_seen = 0;
		g_conf.info_updated_at = glfwGetTime();
		g_conf.time_spent = 0.0;
	}
}