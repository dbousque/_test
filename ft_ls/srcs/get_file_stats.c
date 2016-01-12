/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:53:31 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 16:59:27 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		special_files(int largest[6], struct stat *stats)
{
	long long	tmp;

	tmp = ft_strlen(ft_ntoa_base(MAJOR(stats->st_rdev) / 16, "0123456789"));
	if (tmp > largest[4])
		largest[4] = tmp;
	tmp = ft_strlen(ft_ntoa_base(MINOR(stats->st_rdev), "0123456789"));
	if (tmp > largest[5])
		largest[5] = tmp;
}

void		update_largest(int largest[6], struct stat *stats)
{
	long long	tmp;

	tmp = ft_strlen(ft_ntoa_base(stats->st_nlink, "0123456789"));
	if (tmp > largest[0])
		largest[0] = tmp;
	if (getpwuid(stats->st_uid))
		tmp = ft_strlen(getpwuid(stats->st_uid)->pw_name);
	else
		tmp = ft_strlen(ft_ntoa_base(stats->st_uid, "0123456789"));
	if (tmp > largest[1])
		largest[1] = tmp;
	if (getgrgid(stats->st_gid))
		tmp = ft_strlen(getgrgid(stats->st_gid)->gr_name);
	else
		tmp = ft_strlen(ft_ntoa_base(stats->st_uid, "0123456789"));
	if (tmp > largest[2])
		largest[2] = tmp;
	tmp = ft_strlen(ft_ntoa_base(stats->st_size, "0123456789"));
	if (tmp > largest[3])
		largest[3] = tmp;
	if (S_ISCHR(stats->st_mode) || S_ISBLK(stats->st_mode))
		special_files(largest, stats);
}

struct stat	**get_file_stats(struct dirent **children, char *dir_name,
														int largest[6], int nb)
{
	int			i;
	struct stat	**res;

	if (!(res = (struct stat**)malloc(sizeof(struct stat*) * (nb + 1))))
		return (unexpected_error_null());
	res[nb] = NULL;
	i = 0;
	while (i < 6)
	{
		largest[i] = 0;
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (!(res[i] = (struct stat*)malloc(sizeof(struct stat))))
			return (unexpected_error_null());
		lstat(make_path(children[i]->d_name, dir_name), res[i]);
		if (S_ISLNK(res[i]->st_mode))
			children[i]->d_type = DT_LNK;
		update_largest(largest, res[i]);
		i++;
	}
	return (res);
}
