/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_suitable_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:03:05 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 18:15:41 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	no_shared_salle(t_list *tmp, t_list *visited_salles)
{
	t_list	*tmp2;

	while (tmp)
	{
		tmp2 = visited_salles;
		while (tmp2)
		{
			if (*((int*)tmp->content) == *((int*)tmp2->content))
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	add_salles_to_visited(t_list *path, t_list **visited_salles,
							t_list **visited_salles_end, t_fourm *fourmiliere)
{
	t_list	*tmp;

	tmp = path;
	while (tmp)
	{
		if (*(int*)tmp->content != fourmiliere->end->id
			&& *(int*)tmp->content != fourmiliere->start->id)
		{
			ft_lstaddend(visited_salles_end,
									ft_lstnew((int*)tmp->content, sizeof(int)));
			if (!*visited_salles)
				*visited_salles = *visited_salles_end;
		}
		tmp = tmp->next;
	}
}

void	init_vars(t_list *visited[2], t_list **best_paths,
											t_list *finished_paths, int *len)
{
	*len = listlen(finished_paths);
	best_paths[0] = (t_list*)finished_paths->content;
	visited[0] = NULL;
	visited[1] = NULL;
}

int		**test_paths_from_i(int x, t_list *finished_paths, t_fourm *four,
																int nb_paths)
{
	t_list	*best_pat[nb_paths];
	t_list	*visited[2];
	t_list	*tmp;
	int		len;
	int		nb;

	init_vars(visited, best_pat, finished_paths, &len);
	nb = 1;
	tmp = finished_paths->next;
	add_salles_to_visited(best_pat[0], &visited[0], &visited[1], four);
	while (++x < len)
	{
		if (lon(best_pat, nb, listlen((t_list*)tmp->content), four->nb_fourmis))
			return (path_to_int_paths(best_pat, nb));
		if (no_shared_salle((t_list*)tmp->content, visited[0]))
		{
			best_pat[nb] = (t_list*)tmp->content;
			add_salles_to_visited(best_pat[nb], &visited[0], &visited[1], four);
			nb++;
		}
		if (nb == nb_paths)
			return (path_to_int_paths(best_pat, nb_paths));
		tmp = tmp->next;
	}
	return (NULL);
}

int		**find_suitable_paths(t_list *finished_paths, int nb_paths,
														t_fourm *fourmiliere)
{
	int		i;
	int		len;
	int		**res;

	if (!finished_paths)
		return (NULL);
	len = listlen(finished_paths);
	if (nb_paths == 1)
		return (path_to_int_paths((t_list**)&(finished_paths->content), 1));
	i = 0;
	while (i <= len - nb_paths)
	{
		if ((res = test_paths_from_i(i, finished_paths, fourmiliere,
																	nb_paths)))
			return (res);
		finished_paths = finished_paths->next;
		i++;
	}
	return (NULL);
}
