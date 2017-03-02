

#include "myopengl.h"

char	test_valid_inds(int *faces, size_t ind, t_objfile *objfile)
{
	if (faces[ind] <= 0 || faces[ind] >= (int)objfile->vertices->len)
		return (0);
	if (faces[ind + 1] >= (int)objfile->texture->len)
		return (0);
	if (faces[ind + 2] >= (int)objfile->normals->len)
		return (0);
	if (faces[ind + 3] <= 0 || faces[ind + 3] >= (int)objfile->vertices->len)
		return (0);
	if (faces[ind + 4] >= (int)objfile->texture->len)
		return (0);
	if (faces[ind + 5] >= (int)objfile->normals->len)
		return (0);
	if (faces[ind + 6] <= 0 || faces[ind + 6] >= (int)objfile->vertices->len)
		return (0);
	if (faces[ind + 7] >= (int)objfile->texture->len)
		return (0);
	if (faces[ind + 8] >= (int)objfile->normals->len)
		return (0);
	return (1);
}

char	valid_faces(t_objfile *objfile, int *nb_vertices)
{
	size_t	ind;
	int		*faces;

	faces = (int*)objfile->faces->elts;
	ind = 0;
	*nb_vertices = 0;
	while (ind < objfile->faces->len)
	{
		if (!(test_valid_inds(faces, ind, objfile)))
			return (0);
		ind += 9;
		if (faces[ind] != 0)
			ind -= 6;
		else
			ind++;
		(*nb_vertices) += 3;
	}
	return (1);
}

void	set_vertex(t_objfile *objfile, GLfloat **vertices, size_t faces_ind,
													size_t res_ind, int decal)
{
	float	*raw_vertices;
	float	*normals;
	float	*texture;
	int		*faces;

	faces_ind -= decal;
	raw_vertices = (float*)objfile->vertices->elts;
	normals = (float*)objfile->normals->elts;
	texture = (float*)objfile->texture->elts;
	faces = (int*)objfile->faces->elts;
	(*vertices)[res_ind] = raw_vertices[faces[faces_ind] * 3];
	(*vertices)[res_ind + 1] = raw_vertices[faces[faces_ind] * 3 + 1];
	(*vertices)[res_ind + 2] = raw_vertices[faces[faces_ind] * 3 + 2];
	(*vertices)[res_ind + 3] = texture[faces[faces_ind + 1] * 2];
	(*vertices)[res_ind + 4] = texture[faces[faces_ind + 1] * 2 + 1];
	(*vertices)[res_ind + 5] = normals[faces[faces_ind + 2] * 3];
	(*vertices)[res_ind + 6] = normals[faces[faces_ind + 2] * 3 + 1];
	(*vertices)[res_ind + 7] = normals[faces[faces_ind + 2] * 3 + 2];
}

void	add_normal2(t_objfile *objfile, size_t faces_ind, int decal)
{
	float	v1[3];
	float	v2[3];
	float	*verts;
	int		*faces;
	float	*normals;

	faces = (int*)objfile->faces->elts;
	verts = (float*)objfile->vertices->elts;
	normals = (float*)objfile->calc_normals->elts;
	v1[0] = verts[faces[faces_ind - decal] * 3] - verts[faces[faces_ind] * 3];
	v1[1] = verts[faces[faces_ind - decal] * 3 + 1] - verts[faces[faces_ind] * 3 + 1];
	v1[2] = verts[faces[faces_ind - decal] * 3 + 2] - verts[faces[faces_ind] * 3 + 2];
	v2[0] = verts[faces[faces_ind - decal] * 3] - verts[faces[faces_ind + 3] * 3];
	v2[1] = verts[faces[faces_ind - decal] * 3 + 1] - verts[faces[faces_ind + 3] * 3 + 1];
	v2[2] = verts[faces[faces_ind - decal] * 3 + 2] - verts[faces[faces_ind + 3] * 3 + 2];
	normals[faces[faces_ind - decal] * 3] += v1[1] * v2[2] - v1[2] * v2[1];
	normals[faces[faces_ind - decal] * 3 + 1] += v1[2] * v2[0] - v1[0] * v2[2];
	normals[faces[faces_ind - decal] * 3 + 2] += v1[0] * v2[1] - v1[1] * v2[0];
	normals[faces[faces_ind] * 3] += v1[1] * v2[2] - v1[2] * v2[1];
	normals[faces[faces_ind] * 3 + 1] += v1[2] * v2[0] - v1[0] * v2[2];
	normals[faces[faces_ind] * 3 + 2] += v1[0] * v2[1] - v1[1] * v2[0];
	normals[faces[faces_ind + 3] * 3] += v1[1] * v2[2] - v1[2] * v2[1];
	normals[faces[faces_ind + 3] * 3 + 1] += v1[2] * v2[0] - v1[0] * v2[2];
	normals[faces[faces_ind + 3] * 3 + 2] += v1[0] * v2[1] - v1[1] * v2[0];
}

void	set_normal(t_objfile *objfile, GLfloat **vertices, size_t faces_ind,
													size_t res_ind, int decal)
{
	int		*faces;
	float	*normals;

	faces = (int*)objfile->faces->elts;
	normals = (float*)objfile->calc_normals->elts;
	faces_ind -= decal;
	(*vertices)[res_ind + 5] = normals[faces[faces_ind] * 3];
	(*vertices)[res_ind + 6] = normals[faces[faces_ind] * 3 + 1];
	(*vertices)[res_ind + 7] = normals[faces[faces_ind] * 3 + 2];
}

void	second_pass_add_normals(t_objfile *objfile, GLfloat **vertices)
{
	size_t	x;
	size_t	faces_ind;
	size_t	res_ind;
	int		decal;

	decal = 0;
	res_ind = 0;
	faces_ind = 0;
	while (faces_ind < objfile->faces->len)
	{
		x = 0;
		while (x < 3)
		{
			set_normal(objfile, vertices, faces_ind, res_ind, x == 0 ? decal : 0);
			faces_ind += 3;
			res_ind += 17;
			x++;
		}
		if (((int*)objfile->faces->elts)[faces_ind] != 0)
		{
			decal += 3;
			faces_ind -= 6;
		}
		else
		{
			decal = 0;
			faces_ind++;
		}
	}
}

char	create_calc_normals(t_objfile *objfile, int *nb_vertices)
{
	int		i;

	objfile->calc_normals = new_list(sizeof(float));
	free(objfile->calc_normals->elts);
	if (!(objfile->calc_normals->elts = (float*)malloc(sizeof(float) * (*nb_vertices * 3))))
		return (0);
	i = 0;
	while (i < *nb_vertices * 3)
	{
		((float*)objfile->calc_normals->elts)[i] = 0.0;
		i++;
	}
	objfile->calc_normals->size = (*nb_vertices * 3);
	objfile->calc_normals->len = (*nb_vertices * 3);
	return (1);
}

char	find_top_left(t_objfile *objfile, int *top_left_vertex, float *scale,
												char *vertex_text_already_set)
{
	int		*faces;
	size_t	i;
	float	top_left[2];
	float	lower_right[2];
	float	*vertices;
	char	set_once;

	set_once = 0;
	faces = (int*)objfile->faces->elts;
	vertices = (float*)objfile->vertices->elts;
	i = 0;
	while (i < objfile->faces->len)
	{
		if (!vertex_text_already_set[faces[i]])
		{
			if (!set_once || vertices[faces[i] * 3 + 1] > top_left[1]
				|| (vertices[faces[i] * 3 + 1] == top_left[1]
					&& vertices[faces[i] * 3] < top_left[0]))
			{
				top_left[0] = vertices[faces[i] * 3];
				top_left[1] = vertices[faces[i] * 3 + 1];
				*top_left_vertex = faces[i];
			}
			if (!set_once || vertices[faces[i] * 3 + 1] < top_left[1]
				|| (vertices[faces[i] * 3 + 1] == top_left[1]
					&& vertices[faces[i] * 3] > top_left[0]))
			{
				lower_right[0] = vertices[faces[i] * 3];
				lower_right[1] = vertices[faces[i] * 3 + 1];
			}
			set_once = 1;
		}
		i += 3;
		if (faces[i] == 0)
			i++;
	}
	*scale = fmaxf(fabs(top_left[0] - lower_right[0]),
					fabs(top_left[1] - lower_right[1]));
	return (set_once);
}

void	set_vertex_in_faces(t_objfile *objfile, t_list **vertex_in_faces)
{
	size_t	i;
	int		*faces;
	int		current_face_start;

	current_face_start = 0;
	faces = (int*)objfile->faces->elts;
	i = 0;
	while (i < objfile->faces->len)
	{
		if (!(vertex_in_faces[faces[i]]))
			vertex_in_faces[faces[i]] = new_list(sizeof(int));
		add_to_list(vertex_in_faces[faces[i]], &current_face_start);
		// setting texture coordinate
		faces[i + 1] = faces[i];
		i += 3;
		if (faces[i] == 0)
		{
			i++;
			current_face_start = (int)i;
		}
	}
}

void	get_text_xy(t_objfile *objfile, int known_ind, int unknown_ind,
												float res_xy[2], float scale)
{
	float	*vertices;
	float	*texture;
	float	known_xyz[3];
	float	unknown_xyz[3];
	float	known_text_xy[2];

	vertices = (float*)objfile->vertices->elts;
	texture = (float*)objfile->texture->elts;
	known_xyz[0] = vertices[known_ind * 3];
	known_xyz[1] = vertices[known_ind * 3 + 1];
	known_xyz[2] = vertices[known_ind * 3 + 2];
	unknown_xyz[0] = vertices[unknown_ind * 3];
	unknown_xyz[1] = vertices[unknown_ind * 3 + 1];
	unknown_xyz[2] = vertices[unknown_ind * 3 + 2];
	known_text_xy[0] = texture[known_ind * 2];
	known_text_xy[1] = texture[known_ind * 2 + 1];
	known_xyz[0] = unknown_xyz[0] - known_xyz[0];
	known_xyz[1] = unknown_xyz[1] - known_xyz[1];
	known_xyz[2] = unknown_xyz[2] - known_xyz[2];
	res_xy[0] = known_text_xy[0] + ((known_xyz[0] + known_xyz[2]));
	res_xy[1] = known_text_xy[1] + (known_xyz[1]);
	(void)scale;
}

void	 solve_text_coords(t_objfile *objfile, t_list **vertex_in_faces,
			char *vertex_text_already_set, int current_vertex, float scale,
												float x_text, float y_text)
{
	size_t	i;
	int		x;
	int		*faces;
	int		*face;
	float	new_xy[2];

	faces = (int*)objfile->faces->elts;
	((float*)objfile->texture->elts)[current_vertex * 2] = x_text;
	((float*)objfile->texture->elts)[current_vertex * 2 + 1] = y_text;
	vertex_text_already_set[current_vertex] = 1;
	i = 0;
	while (i < vertex_in_faces[current_vertex]->len)
	{
		face = faces + ((int*)vertex_in_faces[current_vertex]->elts)[i];
		if (!vertex_text_already_set[face[0]])
		{
			get_text_xy(objfile, current_vertex, face[0], new_xy, scale);
			solve_text_coords(objfile, vertex_in_faces, vertex_text_already_set,
					face[0], scale, new_xy[0], new_xy[1]);
		}
		else
		{
			x = 0;
			while (face[x] != 0)
			{
				if (!vertex_text_already_set[face[x]])
				{
					get_text_xy(objfile, face[0], face[x], new_xy, scale);
					solve_text_coords(objfile, vertex_in_faces, vertex_text_already_set,
							face[x], scale, new_xy[0], new_xy[1]);
				}
				x += 3;
			}
		}
		i++;
	}
}

char	generate_texture_coords2(t_objfile *objfile)
{
	t_list	**vertex_in_faces;
	char	*vertex_text_already_set;
	size_t	i;
	float	scale;
	int		top_left_vertex;

	if (!(vertex_in_faces =
			(t_list**)malloc(sizeof(t_list*) * (objfile->vertices->len / 3))))
	{
		return (0);
	}
	if (!(vertex_text_already_set =
				(char*)malloc(sizeof(char) * (objfile->vertices->len / 3))))
	{
		return (0);
	}
	free(objfile->texture->elts);
	if (!(objfile->texture->elts =
		(float*)malloc(sizeof(float) * (objfile->vertices->len / 3) * 2)))
	{
		return (0);
	}
	objfile->texture->size = (objfile->vertices->len / 3) * 2;
	objfile->texture->len = (objfile->vertices->len / 3) * 2;
	i = 0;
	while (i < (objfile->vertices->len / 3) * 2)
	{
		((float*)objfile->texture->elts)[i] = 0.0;
		i++;
	}
	i = 0;
	while (i < objfile->vertices->len)
	{
		vertex_in_faces[i / 3] = NULL;
		vertex_text_already_set[i / 3] = 0;
		i += 3;
	}
	while (find_top_left(objfile, &top_left_vertex, &scale, vertex_text_already_set))
	{
		set_vertex_in_faces(objfile, vertex_in_faces);
		solve_text_coords(objfile, vertex_in_faces, vertex_text_already_set, top_left_vertex, scale, 0.0, 1.0);
	}
	return (1);
}

char	objfile_to_vertices(t_objfile *objfile, GLfloat **verts,
															int *nb_vertices)
{
	size_t	x;
	size_t	faces_ind;
	size_t	res_ind;
	int		decal;

	if (!(valid_faces(objfile, nb_vertices)))
	{
		printf("a face has an invalid index\n");
		return (0);
	}
	if (!(*verts = (GLfloat*)malloc(*nb_vertices * sizeof(GLfloat) * 17)))
		return (0);
	if (objfile->normals->len == 3)
	{
		if (!(create_calc_normals(objfile, nb_vertices)))
			return (0);
	}
	if (objfile->texture->len == 2)
		generate_texture_coords2(objfile);
	decal = 0;
	res_ind = 0;
	faces_ind = 0;
	while (faces_ind < objfile->faces->len)
	{
		x = 0;
		while (x < 3)
		{
			set_vertex(objfile, verts, faces_ind, res_ind, x == 0 ? decal : 0);
			faces_ind += 3;
			res_ind += 17;
			x++;
		}
		// no normal data
		//if (((int*)objfile->faces->elts)[faces_ind - 9 + 2] == 0)
		if (objfile->normals->len == 3)
			add_normal2(objfile, faces_ind - 6, decal + 3);
		if (((int*)objfile->faces->elts)[faces_ind] != 0)
		{
			decal += 3;
			faces_ind -= 6;
		}
		else
		{
			decal = 0;
			faces_ind++;
		}
	}
	if (objfile->normals->len == 3)
		second_pass_add_normals(objfile, verts);
	return (1);
}