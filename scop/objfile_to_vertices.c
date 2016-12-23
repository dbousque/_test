

#include "myopengl.h"

char	test_valid_inds(int *faces, size_t ind, t_objfile *objfile)
{
	if (faces[ind] <= 0 || faces[ind] >= (int)objfile->vertices->len)
		return (0);
	if (faces[ind + 1] >= (int)objfile->texture->len)
		return (0);
	if (faces[ind + 2] >= (int)objfile->normals->len)
		return (0);
	if (faces[ind + 3] <= 0 || faces[ind] >= (int)objfile->vertices->len)
		return (0);
	if (faces[ind + 4] >= (int)objfile->texture->len)
		return (0);
	if (faces[ind + 5] >= (int)objfile->normals->len)
		return (0);
	if (faces[ind + 6] <= 0 || faces[ind] >= (int)objfile->vertices->len)
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

char	objfile_to_vertices(t_objfile *objfile, GLfloat **verts,
															int *nb_vertices)
{
	size_t	x;
	size_t	faces_ind;
	size_t	res_ind;
	int		decal;

	if (!(valid_faces(objfile, nb_vertices)))
		return (0);
	if (!(*verts = (GLfloat*)malloc(*nb_vertices * sizeof(GLfloat) * 8)))
		return (0);
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
			res_ind += 8;
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
	return (1);
}