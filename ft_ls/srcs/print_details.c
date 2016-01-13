/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_details.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:07:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/13 16:26:37 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file_type(struct stat *file_stats)
{
	if (S_ISLNK(file_stats->st_mode))
		ft_putchar('l');
	else if (S_ISDIR(file_stats->st_mode))
		ft_putchar('d');
	else if (S_ISCHR(file_stats->st_mode))
		ft_putchar('c');
	else if (S_ISBLK(file_stats->st_mode))
		ft_putchar('b');
	else if (S_ISSOCK(file_stats->st_mode))
		ft_putchar('s');
	else
		ft_putchar('-');
}

void	print_type_n_rights(struct dirent *file, struct stat *file_stats,
																char *dir_name)
{
	print_file_type(file_stats);
	ft_putchar((file_stats->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((file_stats->st_mode & S_IWUSR) ? 'w' : '-');
	if (file_stats->st_mode & S_ISUID)
		ft_putchar((file_stats->st_mode & S_IXUSR) ? 's' : 'S');
	else
		ft_putchar((file_stats->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((file_stats->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((file_stats->st_mode & S_IWGRP) ? 'w' : '-');
	if (file_stats->st_mode & S_ISGID)
		ft_putchar((file_stats->st_mode & S_IXGRP) ? 's' : 'S');
	else
		ft_putchar((file_stats->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((file_stats->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((file_stats->st_mode & S_IWOTH) ? 'w' : '-');
	if (file_stats->st_mode & S_ISVTX)
		ft_putchar((file_stats->st_mode & S_IXOTH) ? 't' : 'T');
	else
		ft_putchar((file_stats->st_mode & S_IXOTH) ? 'x' : '-');
	if (listxattr(make_path(file->d_name, dir_name),
												NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putchar('@');
	else
		ft_putchar(' ');
}

void	print_nb_hlinks(struct stat *file_stats, int largest)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(ft_ntoa_base(file_stats->st_nlink, "0123456789"));
	while (i < largest - len + 1)
	{
		ft_putchar(' ');
		i++;
	}
	ft_printf("%lld", file_stats->st_nlink);
}

void	print_file_owner(struct stat *file_stats, int largest, t_flags *flags)
{
	int		i;
	int		len;
	char	*user;

	if (!flags->g)
	{
		i = 0;
		if (getpwuid(file_stats->st_uid))
			user = getpwuid(file_stats->st_uid)->pw_name;
		else
			user = ft_ntoa_base(file_stats->st_uid, "0123456789");
		len = ft_strlen(user);
		ft_putchar(' ');
		ft_putstr(user);
		while (i < largest - len + 1)
		{
			ft_putchar(' ');
			i++;
		}
	}
}

void	print_group_name(struct stat *file_stats, int largest)
{
	int		i;
	int		len;
	char	*group;

	i = 0;
	if (getgrgid(file_stats->st_gid))
		group = getgrgid(file_stats->st_gid)->gr_name;
	else
		group = ft_ntoa_base(file_stats->st_gid, "0123456789");
	len = ft_strlen(group);
	ft_putstr(" ");
	ft_putstr(group);
	while (i < largest - len)
	{
		ft_putchar(' ');
		i++;
	}
}
