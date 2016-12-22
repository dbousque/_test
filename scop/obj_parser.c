

#include "myopengl.h"

void	setup_objfile(t_objfile **objfile)
{
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

char	valid_float(char *line, char **end)
{
	size_t	i;
	char	seen_point;

	seen_point = 0;
	if (line[0] == '-' || line[0] == '+')
		line++;
	i = 0;
	while (line[i] && ((line[i] <= '9' && line[i] >= '0') || line[i] == '.'))
	{
		if (line[i] == '.')
		{
			if (seen_point)
				return (0);
			seen_point = 1;
		}
		i++;
	}
	if (i < 1 || !seen_point || line[i - 1] == '.')
		return (0);
	*end = line + i;
	return (1);
}

char	valid_vertex_line(char *line)
{
	line += 2;
	if (!(valid_float(line, &line)))
		return (0);
	if (*line != ' ')
		return (0);
	line += 1;
	if (!(valid_float(line, &line)))
		return (0);
	if (*line != ' ')
		return (0);
	line += 1;
	if (!(valid_float(line, &line)))
		return (0);
	if (*line != '\n')
		return (0);
	return (1);
}

char	add_vertex(t_objfile *objfile, char *line)
{
	float	tmp;

	if (!(valid_vertex_line(line)))
		return (0);
	line += 2;
	tmp = strtof(line, &line);
	if (tmp == HUGE_VALF || tmp == -HUGE_VALF)
		return (0);
	add_to_list(objfile->vertices, &tmp);
	line++;
	tmp = strtof(line, &line);
	add_to_list(objfile->vertices, &tmp);
	line++;
	tmp = strtof(line, &line);
	add_to_list(objfile->vertices, &tmp);
	return (1);
}

char	add_face(t_objfile *objfile, char *line)
{
	if (!(valid_face_line(line)))
		return (0);
	return (1);
}

char	interpret_line(t_objfile *objfile, char *line)
{
	if (startswith(line, "v "))
		return (add_vertex(objfile, line));
	if (startswith(line, "f "))
		return (add_face(objfile, line));
	return (1);
}

t_objfile	*parse_objfile(char *path)
{
	FILE		*fp;
	char		*line;
	size_t		len;
	t_objfile	*objfile;

	setup_objfile(&objfile);
	if (!objfile)
		return (NULL);
	len = 0;
	line = NULL;
	fp = fopen(path, "r");
	if (!fp)
		return (NULL);
	while (getline(&line, &len, fp) != -1)
	{
		if (!(interpret_line(objfile, line)))
			return (NULL);
		free(line);
		line = NULL;
	}
	fclose(fp);
	return (objfile);
}