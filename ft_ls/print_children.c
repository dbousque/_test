/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:44:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 16:45:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_children_details(struct dirent **children, t_flags *flags,
														int nb, char *dir_name)
{
	int			i;
	struct stat	**file_stats;
	int			largest[6];

	(void)flags;
	if (!(file_stats = get_file_stats(children, dir_name, largest, nb)))
		return (0);
	i = 0;
	print_total(file_stats, nb, dir_name);
	while (i < nb)
	{
		print_type_n_rights(children[i], file_stats[i], dir_name);
		print_nb_hlinks(file_stats[i], largest[0]);
		print_file_owner(file_stats[i], largest[1]);
		print_group_name(file_stats[i], largest[2]);
		print_file_size(file_stats[i], largest);
		print_date(file_stats[i]);
		ft_putchar(' ');
		ft_putstr(children[i]->d_name);
		if (S_ISLNK(file_stats[i]->st_mode))
			print_links_to(children[i], dir_name);
		ft_putchar('\n');
		i++;
	}
	return (0);
}

int		print_children_regular(struct dirent **children, int nb)
{
	char	**strings;
	int		i;

	if (!(strings = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (0);
	strings[nb] = NULL;
	i = 0;
	while (i < nb)
	{
		strings[i] = children[i]->d_name;
		i++;
	}
	return (print_string_array_columns(strings, nb));
}

int		print_children_regular_std(struct dirent **children, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		ft_putstr(children[i]->d_name);
		ft_putchar('\n');
		i++;
	}
	return (1);
}
