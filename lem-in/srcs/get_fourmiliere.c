/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fourmiliere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:59:18 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/09 15:48:56 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		listlen(t_list *list)
{
	int		length;

	length = 0;
	while (list)
	{
		length++;
		list = list->next;
	}
	return (length);
}

int		accessible_list_to_array(t_salle **salles)
{
	t_list	*tmp;
	int		i;
	int		len;
	int		x;

	i = 0;
	while (salles[i])
	{
		tmp = salles[i]->tmp_accessible_salles;
		len = listlen(tmp);
		if (!(salles[i]->accessible_salles = (t_salle**)malloc(sizeof(t_salle*)
														* (len + 1))))
			return (0);
		salles[i]->accessible_salles[len] = NULL;
		x = 0;
		while (tmp)
		{
			salles[i]->accessible_salles[x] = *((t_salle**)tmp->content);
			tmp = tmp->next;
			x++;
		}
		i++;
	}
	return (1);
}

void	free_tmp_lists(t_salle **salles)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;

	i = 0;
	while (salles[i])
	{
		tmp = salles[i]->tmp_accessible_salles;
		while (tmp)
		{
			tmp2 = tmp->next;
			free(tmp);
			tmp = NULL;
			tmp = tmp2;
		}
		salles[i]->tmp_accessible_salles = NULL;
		salles[i]->tmp_accessible_salles_end = NULL;
		i++;
	}
}

t_fourm	*salles_to_fourmiliere(int nb_fourmis, t_salle **salles,
								t_salle *start_salle, t_salle *end_salle)
{
	t_fourm	*res;

	if (!(res = (t_fourm*)malloc(sizeof(t_fourm))))
		return (NULL);
	res->nb_fourmis = nb_fourmis;
	res->salles = salles;
	res->start = start_salle;
	res->end = end_salle;
	res->flags = NULL;
	return (res);
}

t_fourm	*get_fourmiliere(t_salle **start_salle, t_salle **end_salle,
																t_list **lines)
{
	t_salle	**salles;
	char	*line;
	int		nb_fourm;
	t_list	*lines_end;

	if (get_next_line(0, &line) == -1 || !only_numbers(line) || line[0] == '0')
		return (NULL);
	nb_fourm = ft_atoi(line);
	lines_end = NULL;
	ft_lstaddend(&lines_end,
			ft_lstnew(line, sizeof(char) * (ft_strlen(line) + 1)));
	*lines = lines_end;
	free(line);
	salles = parse_salles(start_salle, end_salle, &line, &lines_end);
	if (!salles)
		return (NULL);
	if (!(*start_salle) || !(*end_salle))
		return (NULL);
	if (!(get_tubes(salles, line, &lines_end)))
		return (NULL);
	if (!(accessible_list_to_array(salles)))
		return (NULL);
	free_tmp_lists(salles);
	return (salles_to_fourmiliere(nb_fourm, salles, *start_salle, *end_salle));
}
