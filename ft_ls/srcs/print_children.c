/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:44:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 17:06:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_children_details(struct dirent **children, t_flags *flags,
														int nb, char *dir_name)
{
	int			i;
	struct stat	**file_stats;
	int			largest[6];

	if (!(file_stats = get_file_stats(children, dir_name, largest, nb)))
		return (0);
	i = 0;
	print_total(file_stats, nb, dir_name);
	while (i < nb)
	{
		print_type_n_rights(children[i], file_stats[i], dir_name);
		print_nb_hlinks(file_stats[i], largest[0]);
		print_file_owner(file_stats[i], largest[1], flags);
		print_group_name(file_stats[i], largest[2]);
		print_file_size(file_stats[i], largest);
		print_date(file_stats[i], flags);
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

void	reverse_children(struct dirent **children, int len)
{
	int				end;
	int				start;
	struct dirent	*tmp;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		tmp = children[start];
		children[start] = children[end];
		children[end] = tmp;
		start++;
		end--;
	}
}

void	print_children(struct dirent **children, t_flags *flags, int nb_child,
																char *dir_name)
{
	if (flags->t)
		sort_by_date(children, nb_child, dir_name, (flags->u ? 0 : 1));
	else if (flags->s)
		sort_by_size(children, nb_child, dir_name);
	else
		sort_by_name(children, nb_child);
	if (flags->r)
		reverse_children(children, nb_child);
	if (flags->l)
		print_children_details(children, flags, nb_child, dir_name);
	else if (flags->minus)
		print_children_regular_std(children, nb_child);
	else
		print_children_regular(children, nb_child);
}
