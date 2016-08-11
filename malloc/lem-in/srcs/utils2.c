/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 18:22:28 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 19:39:37 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_error(void)
{
	ft_putendl_fd("ERROR", 2);
	return (0);
}

void	put_lines(t_list *lines)
{
	while (lines)
	{
		ft_putendl((char*)lines->content);
		lines = lines->next;
	}
}

int		turns_required_for_n_fourmis(int path_len, int nb_fourmis)
{
	int		res;

	res = nb_fourmis - 1 + (path_len - 1);
	return (res);
}

/*
** adding_path_will_make_way_longer
*/

char	lon(t_list **best_paths, int nb_best, int current_path_len,
																int nb_fourmis)
{
	int		steps_witho;
	int		steps_with;

	steps_witho = turns_required_for_n_fourmis(listlen(best_paths[nb_best - 1]),
														nb_fourmis / nb_best);
	steps_with = turns_required_for_n_fourmis(current_path_len, 1);
	if (steps_witho <= steps_with)
		return (1);
	return (0);
}

void	put_best_paths(int **best_paths, t_fourm *fourm)
{
	int		i;
	int		x;

	i = 0;
	ft_printf("\n{cyan}BEST PATHS :{eoc}\n");
	while (best_paths[i])
	{
		ft_printf("  %d)  ", i + 1);
		x = int_tab_len(best_paths[i]) - 1;
		while (x >= 0)
		{
			if (x == 0)
				ft_printf("{red}");
			ft_putstr(fourm->salles[best_paths[i][x]]->name);
			if (x == 0)
				ft_printf("{eoc}");
			else
				ft_putstr(" -> ");
			x--;
		}
		i++;
		ft_putchar('\n');
	}
}
