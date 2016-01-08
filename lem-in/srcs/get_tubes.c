/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tubes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:56:09 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 16:57:25 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_salle	*get_salle_by_name(t_salle **salles, char *name)
{
	int		i;

	i = 0;
	while (salles[i])
	{
		if (ft_strcmp(salles[i]->name, name) == 0)
			return (salles[i]);
		i++;
	}
	return (NULL);
}

int		add_tube_from_to(t_salle *from, t_salle *to)
{
	t_list	*new;

	if (!(new = ft_lstnew(&to, sizeof(t_salle**))))
		return (0);
	ft_lstaddend(&(from->tmp_accessible_salles_end), new);
	if (!(from->tmp_accessible_salles))
		from->tmp_accessible_salles = from->tmp_accessible_salles_end;
	return (1);
}

int		add_tubes(t_salle **salles, char *line)
{
	char	**parts;
	t_salle	*first;
	t_salle	*second;

	if (!(parts = ft_strsplit(line, '-')))
		return (0);
	if (!(first = get_salle_by_name(salles, parts[0])))
		return (0);
	if (!(second = get_salle_by_name(salles, parts[1])))
		return (0);
	if (first == second)
		return (0);
	if (!(add_tube_from_to(first, second)))
		return (0);
	if (!(add_tube_from_to(second, first)))
		return (0);
	return (1);
}

int		get_tubes(t_salle **salles, char *line, t_list **lines_end)
{
	while (is_tube_description(line) || is_comment(line))
	{
		ft_lstaddend(lines_end,
				ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1)));
		if (!is_comment(line))
		{
			if (!(add_tubes(salles, line)))
				return (0);
		}
		free(line);
		if (get_next_line(0, &line) == -1)
			return (0);
	}
	free(line);
	return (1);
}
