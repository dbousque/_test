/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_salles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:27:54 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 16:28:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	salle_name_already_used(t_list *salles, t_salle *salle)
{
	while (salles && salles->next)
	{
		if (ft_strcmp(((t_salle*)salles->content)->name, salle->name) == 0)
			return (1);
		salles = salles->next;
	}
	return (0);
}

char	is_comment(char *line)
{
	if (line[0] != '#')
		return (0);
	return (1);
}

t_salle	**free_n_return_null(t_list *salles_end)
{
	free(((t_salle*)salles_end->content)->name);
	free(((t_salle*)salles_end->content));
	free(salles_end);
	salles_end = NULL;
	return (NULL);
}

t_salle	**not_valid_or_list_to_salles(char **line, t_list *salles)
{
	if (is_input_correct(*line) == -1
		|| (!is_tube_description(*line) && !is_comment(*line)))
	{
		free(*line);
		return (NULL);
	}
	return (list_to_salles(salles));
}

t_salle	**parse_salles(t_salle **start_salle, t_salle **end_salle,
												char **line, t_list **lines_end)
{
	t_list	*salles;
	t_list	*salles_end;
	t_salle	**start_end[2];

	salles = NULL;
	salles_end = NULL;
	if (get_next_line(0, line) == -1)
		return (NULL);
	start_end[0] = start_salle;
	start_end[1] = end_salle;
	while (is_input_correct(*line) == 1 && line && ft_strlen(*line) > 0)
	{
		if (!(add_to_salles(&salles_end, line, start_end, lines_end)))
			return (NULL);
		if (!salles)
			salles = salles_end;
		if (salle_name_already_used(salles, (t_salle*)salles_end->content))
			return (free_n_return_null(salles_end));
		ft_lstaddend(lines_end,
				ft_lstnew(*line, sizeof(char) * (ft_strlen(*line) + 1)));
		free(*line);
		if (get_next_line(0, line) == -1)
			return (NULL);
	}
	return (not_valid_or_list_to_salles(line, salles));
}
