/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vertices.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:12:52 by dbousque          #+#    #+#             */
/*   Updated: 2017/03/02 18:12:53 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myopengl.h"

char	return_vertex_error(char *msg, char *line, size_t line_nb)
{
	printf("line %ld ; %s : %s", line_nb, msg, line);
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
	while (line[i] && ((line[i] <= '9' && line[i] >= '0')
			|| line[i] == '.'
			|| (line[i] == 'e' && line[i + 1] == '-')
			|| (line[i] == '-' && line[i - 1] == 'e')
			|| (line[i] == 'e' && line[i + 1] == '+')
			|| (line[i] == '+' && line[i - 1] == 'e')))
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

char	valid_vertex_line(char *line, size_t line_nb)
{
	if (!(valid_float(line, &line)) && !(valid_int(line, &line)))
		return (return_vertex_error("invalid number on line", line, line_nb));
	if (*line != ' ')
		return (return_vertex_error("separator not a space", line, line_nb));
	line += 1;
	if (!(valid_float(line, &line)) && !(valid_int(line, &line)))
		return (return_vertex_error("invalid number on line", line, line_nb));
	if (*line != ' ')
		return (return_vertex_error("separator not a space", line, line_nb));
	line += 1;
	if (!(valid_float(line, &line)) && !(valid_int(line, &line)))
		return (return_vertex_error("invalid number on line", line, line_nb));
	if (*line != '\n' && *line != '\0')
		return (return_vertex_error("no \\n at end of line", line, line_nb));
	return (1);
}

char	valid_texture_line(char *line, size_t line_nb)
{
	if (!(valid_float(line, &line)) && !(valid_int(line, &line)))
		return (return_vertex_error("invalid number on line", line, line_nb));
	if (*line != ' ')
		return (return_vertex_error("separator not a space", line, line_nb));
	line += 1;
	if (!(valid_float(line, &line)) && !(valid_int(line, &line)))
		return (return_vertex_error("invalid number on line", line, line_nb));
	//if (*line != '\n' && *line != '\0')
	//	return (return_vertex_error("no \\n at end of line", line, line_nb));
	return (1);
}

char	add_vertex(t_objfile *objfile, char *line, size_t line_nb)
{
	float	tmp;

	line += 2;
	while (*line == ' ')
		line++;
	if (!(valid_vertex_line(line, line_nb)))
		return (0);
	tmp = strtof(line, &line);
	if (tmp == HUGE_VALF || tmp == -HUGE_VALF)
		return (return_vertex_error("float overflow", line, line_nb));
	add_to_list(objfile->vertices, &tmp);
	line++;
	tmp = strtof(line, &line);
	add_to_list(objfile->vertices, &tmp);
	line++;
	tmp = strtof(line, &line);
	add_to_list(objfile->vertices, &tmp);
	return (1);
}

char	add_normal(t_objfile *objfile, char *line, size_t line_nb)
{
	float	tmp;

	line += 3;
	while (*line == ' ')
		line++;
	if (!(valid_vertex_line(line, line_nb)))
		return (0);
	tmp = strtof(line, &line);
	if (tmp == HUGE_VALF || tmp == -HUGE_VALF)
		return (return_vertex_error("float overflow", line, line_nb));
	add_to_list(objfile->normals, &tmp);
	line++;
	tmp = strtof(line, &line);
	add_to_list(objfile->normals, &tmp);
	line++;
	tmp = strtof(line, &line);
	add_to_list(objfile->normals, &tmp);
	return (1);
}

char	add_texture(t_objfile *objfile, char *line, size_t line_nb)
{
	float	tmp;

	line += 3;
	while (*line == ' ')
		line++;
	if (!(valid_texture_line(line, line_nb)))
		return (0);
	tmp = strtof(line, &line);
	if (tmp == HUGE_VALF || tmp == -HUGE_VALF)
		return (return_vertex_error("float overflow", line, line_nb));
	add_to_list(objfile->texture, &tmp);
	line++;
	tmp = strtof(line, &line);
	add_to_list(objfile->texture, &tmp);
	return (1);
}
