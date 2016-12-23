

#include "myopengl.h"

void	setup_objfile(t_objfile **objfile)
{
	float	tmp_float;

	if (!(*objfile = (t_objfile*)malloc(sizeof(t_objfile))))
	{
		*objfile = NULL;
		return ;
	}
	(*objfile)->objname = NULL;
	(*objfile)->vertices = new_list(sizeof(float));
	(*objfile)->texture = new_list(sizeof(float));
	(*objfile)->normals = new_list(sizeof(float));
	(*objfile)->faces = new_list(sizeof(int));
	tmp_float = 0.0;
	add_to_list((*objfile)->vertices, &tmp_float);
	add_to_list((*objfile)->vertices, &tmp_float);
	add_to_list((*objfile)->vertices, &tmp_float);
	add_to_list((*objfile)->texture, &tmp_float);
	add_to_list((*objfile)->texture, &tmp_float);
	add_to_list((*objfile)->normals, &tmp_float);
	add_to_list((*objfile)->normals, &tmp_float);
	add_to_list((*objfile)->normals, &tmp_float);
}

char	startswith(char *str, char *begin)
{
	size_t	i;

	i = 0;
	while (str[i] && begin[i] && str[i] == begin[i])
		i++;
	if (!begin[i])
		return (1);
	return (0);
}

char	interpret_line(t_objfile *objfile, char *line, size_t line_nb)
{
	if (startswith(line, "v "))
		return (add_vertex(objfile, line, line_nb));
	if (startswith(line, "f "))
		return (add_face(objfile, line, line_nb));
	return (1);
}

t_objfile	*parse_objfile(char *path)
{
	FILE		*fp;
	char		*line;
	size_t		len;
	t_objfile	*objfile;
	size_t		line_nb;

	setup_objfile(&objfile);
	if (!objfile)
		return (NULL);
	len = 0;
	line = NULL;
	fp = fopen(path, "r");
	if (!fp)
	{
		printf("file could not be opened\n");
		return (NULL);
	}
	line_nb = 1;
	while (getline(&line, &len, fp) != -1)
	{
		if (!(interpret_line(objfile, line, line_nb)))
			return (NULL);
		free(line);
		line = NULL;
		line_nb++;
	}
	fclose(fp);
	return (objfile);
}