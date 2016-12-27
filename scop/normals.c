

#include "myopengl.h"

void	calculate_raw_normals(GLfloat *v, int nb_vertices)
{
	int			i;
	t_vec		*v1;
	t_vec		*v2;
	float		*v1e;
	float		*v2e;

	i = 0;
	while (i < nb_vertices)
	{
		v1 = vec3_sub(new_vec3(v[i * 8 + 0], v[i * 8 + 1], v[i * 8 + 2]),
		new_vec3(v[(i + 1) * 8 + 0], v[(i + 1) * 8 + 1], v[(i + 1) * 8 + 2]));
		v2 = vec3_sub(new_vec3(v[i * 8 + 0], v[i * 8 + 1], v[i * 8 + 2]),
		new_vec3(v[(i + 2) * 8 + 0], v[(i + 2) * 8 + 1], v[(i + 2) * 8 + 2]));
		v1e = v1->elts;
		v2e = v2->elts;
		v[i * 8 + 5] = v1e[1] * v2e[2] - v1e[2] * v2e[1];
		v[i * 8 + 6] = v1e[2] * v2e[0] - v1e[0] * v2e[2];
		v[i * 8 + 7] = v1e[0] * v2e[1] - v1e[1] * v2e[0];
		v[(i + 1) * 8 + 5] = v1e[1] * v2e[2] - v1e[2] * v2e[1];
		v[(i + 1) * 8 + 6] = v1e[2] * v2e[0] - v1e[0] * v2e[2];
		v[(i + 1) * 8 + 7] = v1e[0] * v2e[1] - v1e[1] * v2e[0];
		v[(i + 2) * 8 + 5] = v1e[1] * v2e[2] - v1e[2] * v2e[1];
		v[(i + 2) * 8 + 6] = v1e[2] * v2e[0] - v1e[0] * v2e[2];
		v[(i + 2) * 8 + 7] = v1e[0] * v2e[1] - v1e[1] * v2e[0];
		i += 3;
	}
}