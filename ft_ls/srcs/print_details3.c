/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_details3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:31:11 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 16:42:57 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_size(struct stat *file_stats, int largest[6])
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(ft_ntoa_base(MAJOR(file_stats->st_rdev) / 16,
																"0123456789"));
	while (i < largest[4] - len + 3)
	{
		ft_putchar(' ');
		i++;
	}
	ft_printf("%lld,", MAJOR(file_stats->st_rdev) / 16);
	i = 0;
	len = ft_strlen(ft_ntoa_base(MINOR(file_stats->st_rdev), "0123456789"));
	while (i < largest[5] - len + 1)
	{
		ft_putchar(' ');
		i++;
	}
	ft_printf("%lld", MINOR(file_stats->st_rdev));
}

void	print_file_size(struct stat *file_stats, int largest[6])
{
	int		i;
	int		len;

	if (!S_ISBLK(file_stats->st_mode) && !S_ISCHR(file_stats->st_mode))
	{
		i = 0;
		len = ft_strlen(ft_ntoa_base(file_stats->st_size, "0123456789"));
		while (i < largest[3] - len + 2 + largest[4] + largest[5]
							+ ((largest[4] != 0 || largest[5] != 0) ? 2 : 0))
		{
			ft_putchar(' ');
			i++;
		}
		ft_printf("%lld", file_stats->st_size);
	}
	else
		print_size(file_stats, largest);
}

void	print_links_to(struct dirent *child, char *dir_name)
{
	char	buf[1025];
	int		ret;

	ret = readlink(make_path(child->d_name, dir_name), buf, 1024);
	if (ret == -1)
		print_errno(errno, make_path(child->d_name, dir_name));
	ft_putstr(" -> ");
	buf[ret] = '\0';
	ft_putstr(buf);
}

void	print_total(struct stat **file_stats, int nb, char *dir_name)
{
	long	res;
	int		i;

	if (dir_name && nb > 0)
	{
		res = 0;
		i = 0;
		while (i < nb)
		{
			res += file_stats[i]->st_blocks;
			i++;
		}
		ft_putstr("total ");
		ft_putstr(ft_ntoa_base(res, "0123456789"));
		ft_putchar('\n');
	}
}
