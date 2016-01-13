/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:31:12 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 12:15:08 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		min_end_start(t_fourm *fourmiliere)
{
	int		len_start;
	int		len_end;

	len_start = 0;
	while (fourmiliere->start->accessible_salles[len_start])
		len_start++;
	len_end = 0;
	while (fourmiliere->end->accessible_salles[len_end])
		len_end++;
	if (len_end < len_start)
		return (len_end);
	return (len_start);
}

int		**path_to_int_paths(t_list **best_paths, int nb_paths)
{
	int		**res;
	t_list	*tmp;
	int		x;
	int		i;

	if (!(res = (int**)malloc(sizeof(int*) * (nb_paths + 1))))
		return (NULL);
	res[nb_paths] = NULL;
	i = 0;
	while (i < nb_paths)
	{
		if (!(res[i] = (int*)malloc(sizeof(int) * listlen(best_paths[i]) + 1)))
			return (NULL);
		res[i][listlen(best_paths[i])] = -1;
		x = 0;
		tmp = best_paths[i];
		while (tmp)
		{
			res[i][x] = *((int*)tmp->content);
			x++;
			tmp = tmp->next;
		}
		i++;
	}
	return (res);
}

int		find_best_paths_and_travel(t_fourm *fourmiliere, t_list *lines,
												int nb_paths)
{
	int		**best_paths;
	t_list	*finished_paths;

	if (!(best_paths = find_best_paths(fourmiliere, nb_paths, &finished_paths)))
	{
		nb_paths--;
		while (nb_paths > 0 && !(best_paths =
			find_suitable_paths(finished_paths, nb_paths, fourmiliere)))
			nb_paths--;
		if (!best_paths)
			return (ft_error());
	}
	put_lines(lines);
	if (fourmiliere->flags->b)
		put_best_paths(best_paths, fourmiliere);
	return (make_fourmi_travel(best_paths, fourmiliere, intintlen(best_paths),
																		NULL));
}

int		main(int argc, char **argv)
{
	t_fourm	*fourmiliere;
	t_salle	*start_end_salle[2];
	int		nb_paths_to_find;
	t_list	*lines;
	t_flag	*flags;

	flags = void_flags();
	start_end_salle[0] = NULL;
	start_end_salle[1] = NULL;
	if (!get_flags(argc, argv, flags))
		return (0);
	if (!flags)
		return (ft_error());
	if (!(fourmiliere = get_fourmiliere(&start_end_salle[0],
												&start_end_salle[1], &lines)))
		return (ft_error());
	if (!(nb_paths_to_find = min_end_start(fourmiliere)))
		return (ft_error());
	fourmiliere->flags = flags;
	return (find_best_paths_and_travel(fourmiliere, lines, nb_paths_to_find));
}
