

#include "myopengl.h"

int		main(void)
{
	t_objfile	*objfile;
	size_t		i;
	float		*elts;

	objfile = parse_objfile("test.obj");
	if (!objfile)
		return (0);
	i = 0;
	elts = (float*)objfile->vertices->elts;
	while (i < objfile->vertices->len)
	{
		printf("%f ", elts[i]);
		i++;
	}
	printf("\n");
	return (0);
}