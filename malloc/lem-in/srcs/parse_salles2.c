/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_salles2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:32:47 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 16:34:08 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	free_parts_n_salle(char **parts, t_salle **salle, char return_val)
{
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	free(*salle);
	*salle = NULL;
	return (return_val);
}

char	add_to_salles(t_list **salles_end, char **line,
							t_salle **str_end[2], t_list **lines_end)
{
	char	**parts;
	char	start_end;
	t_salle	*salle;

	start_end = is_start_or_end_salle(line, str_end[0], str_end[1], lines_end);
	if (start_end == -1)
		return (0);
	else if (start_end == -2)
		return (1);
	if (!(parts = ft_strsplit(*line, ' ')))
		return (0);
	if (!(salle = new_salle(parts[0], ft_atoi(parts[1]), ft_atoi(parts[2]))))
		return (0);
	ft_lstaddend(salles_end, ft_lstnew(salle, sizeof(t_salle)));
	if (start_end == 1)
		*str_end[0] = (t_salle*)((*salles_end)->content);
	else if (start_end == 2)
		*str_end[1] = (t_salle*)((*salles_end)->content);
	return (free_parts_n_salle(parts, &salle, 1));
}

t_salle	**list_to_salles(t_list *salles)
{
	t_salle	**res;
	t_list	*tmp;
	int		length;

	tmp = salles;
	length = 0;
	while (tmp)
	{
		length++;
		tmp = tmp->next;
	}
	if (!(res = (t_salle**)malloc(sizeof(t_salle*) * (length + 1))))
		return (NULL);
	res[length] = NULL;
	length = 0;
	tmp = salles;
	while (tmp)
	{
		res[length] = (t_salle*)tmp->content;
		length++;
		salles = tmp;
		tmp = tmp->next;
		free(salles);
	}
	return (res);
}

char	is_tube_description(char *line)
{
	char	**parts;
	int		i;

	if (ft_strlen(line) < 3)
		return (0);
	if (!(parts = ft_strsplit(line, '-')) || strstrlen(parts) != 2)
	{
		i = 0;
		while (parts[i])
		{
			free(parts[i]);
			i++;
		}
		free(parts);
		return (0);
	}
	free(parts[0]);
	free(parts[1]);
	free(parts);
	return (1);
}
