/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:38:47 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 16:50:51 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_other_params(char **other_params, t_flags *flags)
{
	struct dirent	**children;
	int				l;

	if (!(children = strstr_to_dirent_array(other_params, &l)))
		return (0);
	print_children(children, flags, l, NULL);
	return (2);
}

void	order_dirs(struct dirent **dirs, t_flags *flags, int l)
{
	if (flags->t)
		sort_by_date(dirs, l, NULL, 1);
	else
		sort_by_name(dirs, l);
	if (flags->r)
		reverse_children(dirs, l);
}

void	opendirectory(struct dirent **dirs, t_flags *flags, int i)
{
	DIR		*tmp_dir;
	t_list	*dir_children;

	if ((tmp_dir = opendir(dirs[i]->d_name)))
	{
		dir_children = ft_lstnew(NULL, 0);
		listdir(tmp_dir, flags, dirs[i]->d_name, dir_children);
		closedir(tmp_dir);
		if (flags->r_maj && dir_children->next)
		{
			ft_putchar('\n');
			print_dir_params(list_to_string_array(dir_children->next),
																flags, NULL, 1);
		}
	}
	else
		print_errno(errno, dirs[i]->d_name);
}

int		print_dir_params(char **dir_params, t_flags *flags,
										char **other_params, char print_name)
{
	struct dirent	**dirs;
	int				i;
	int				l;

	if (!(dirs = strstr_to_dirent_array(dir_params, &l)))
		return (0);
	order_dirs(dirs, flags, l);
	i = 0;
	while (i < l)
	{
		if (i != 0)
			ft_putchar('\n');
		if (i != 0 || (other_params && other_params[0]) || i + 1 < l
			|| print_name)
		{
			ft_putstr(dirs[i]->d_name);
			ft_putendl(":");
		}
		opendirectory(dirs, flags, i);
		i++;
	}
	return (1);
}

int		print_params(char **dir_params, char **other_params, t_flags *flags,
																int nb_params)
{
	int		res;

	res = print_other_params(other_params, flags);
	if (res == 2 && dir_params[0])
		ft_putchar('\n');
	if (nb_params <= 1)
		print_dir_params(dir_params, flags, other_params, 0);
	else
		print_dir_params(dir_params, flags, other_params, 1);
	return (0);
}
