

#include "myopengl.h"

char	parse_object_line(char *line, t_globj **obj)
{
	if (startswith(line, "obj "))
	{
		if (*obj)
		{
			ft_putstr("obj appears twice\n");
			return (0);
		}
		*obj = new_obj_from_path(line + 4, 1);
	}
	if (!*obj)
	{
		ft_putstr("obj should be defined at the top of the file\n");
		return (0);
	}
	if (startswith(line, "diffuse "))
		load_texture_to_obj(*obj, line + 8);
	if (startswith(line, "specular "))
		load_specular_map_to_obj(*obj, line + 9);
	if (startswith(line, "normal "))
		load_normal_map_to_obj(*obj, line + 7);
	if (startswith(line, "spec_strength "))
		(*obj)->specular_strength = atoi(line + 14);
	return (1);
}

char	load_object_file(char *filename, t_list *objs)
{
	FILE	*fp;
	char	*line;
	size_t	len;
	t_globj	*obj;

	line = NULL;
	obj = NULL;
	len = 0;
	fp = fopen(filename, "r");
	if (!fp)
	{
		printf("file %s could not be opened\n", filename);
		return (0);
	}
	while (getline(&line, &len, fp) != -1)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!(parse_object_line(line, &obj)))
		{
			fclose(fp);
			return (0);
		}
	}
	fclose(fp);
	attach_shader_program_to_obj(obj, g_obj_program);
	add_to_list(objs, &obj);
	return (1);
}