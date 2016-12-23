

#include "myopengl.h"

int		main(void)
{
	t_objfile	*objfile;
	//size_t		i;
	//float		*elts;
	//int			*faces;
	GLfloat		*vertices;
	int			nb_vertices;

	objfile = parse_objfile("test.obj");
	if (!objfile)
		return (0);
	/*i = 0;
	elts = (float*)objfile->vertices->elts;
	while (i < objfile->vertices->len)
	{
		printf("%f ", elts[i]);
		i++;
	}
	printf("\n");
	faces = (int*)objfile->faces->elts;
	i = 0;
	while (i < objfile->faces->len)
	{
		printf("%d ", faces[i]);
		i++;
	}
	printf("\n");*/
	if (!(objfile_to_vertices(objfile, &vertices, &nb_vertices)))
	{
		printf("could not get vertices from objfile\n");
		return (0);
	}
	printf("nb_vertices : %d\n", nb_vertices);
	int i = 0;
	int x;
	while (i < nb_vertices)
	{
		x = 0;
		while (x < 24)
		{
			if (x % 8 == 0)
				printf("| ");
			printf("%5.2f ", vertices[i * 24 + x]);
			x++;
		}
		printf("\n");
		i++;
	}
	return (0);
}