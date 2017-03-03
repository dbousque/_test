

#include "myopengl.h"

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
		vertices[i * 17] -= x_diff;
		vertices[i * 17 + 1] -= y_diff;
		vertices[i * 17 + 2] -= z_diff;
		i++;
	}
}

float	adjust_scale(GLfloat x_y_z_mmax[6])
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
	return (3.0 / biggest_diff);
}

float	adjust_obj(GLfloat *vertices, int nb_vertices)
{
	GLfloat		x_y_z_mmax[6];
	int			i;

	i = 0;
	while (i < nb_vertices)
	{
		if (i == 0 || vertices[i * 17] < x_y_z_mmax[0])
			x_y_z_mmax[0] = vertices[i * 17];
		if (i == 0 || vertices[i * 17] > x_y_z_mmax[1])
			x_y_z_mmax[1] = vertices[i * 17];
		if (i == 0 || vertices[i * 17 + 1] < x_y_z_mmax[2])
			x_y_z_mmax[2] = vertices[i * 17 + 1];
		if (i == 0 || vertices[i * 17 + 1] > x_y_z_mmax[3])
			x_y_z_mmax[3] = vertices[i * 17 + 1];
		if (i == 0 || vertices[i * 17 + 2] < x_y_z_mmax[4])
			x_y_z_mmax[4] = vertices[i * 17 + 2];
		if (i == 0 || vertices[i * 17 + 2] > x_y_z_mmax[5])
			x_y_z_mmax[5] = vertices[i * 17 + 2];
		i++;
	}
	center_vertices(vertices, nb_vertices, x_y_z_mmax);
	return (adjust_scale(x_y_z_mmax));
}

t_light		*new_std_light(float r, float g, float b, float ambient_strength)
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
	light->ambient_strength = ambient_strength;
	light->obj->x = 2.0;
	light->obj->z = 1.0;
	light->obj->y = 0.5;
	light->r = r;
	light->g = g;
	light->b = b;
	return (light);
}