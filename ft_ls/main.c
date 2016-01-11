/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/11 18:21:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		unexpected_error(void)
{
	ft_putendl_fd("ft_ls: unexpected error", 2);
	return (0);
}

void	*unexpected_error_null(void)
{
	ft_putendl_fd("ft_ls: unexpected error", 2);
	return (NULL);
}

void	print_errno(int error, char *filename)
{
	ft_putstr_fd("ft_ls: ", 2);
	if (filename[0] == '\0')
		ft_putstr_fd("fts_open", 2);
	else
		ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(error), 2);
}

struct dirent	**children_list_to_array(t_list *children_list, int length)
{
	struct dirent	**res;
	t_list			*tmp;
	int				i;

	if (!(res = (struct dirent**)malloc(sizeof(struct dirent*) * (length + 1))))
		return (NULL);
	res[length] = NULL;
	i = 0;
	while (children_list)
	{
		res[i] = ((struct dirent*)children_list->content);
		tmp = children_list;
		children_list = children_list->next;
		free(tmp);
		i++;
	}
	return (res);
}

char	*make_path(char *filename, char *dir_name)
{
	int		len;

	if (!dir_name)
		return (filename);
	len = ft_strlen(dir_name);
	if (dir_name[len - 1] != '/')
		dir_name = ft_strjoin(dir_name, "/");
	return (ft_strjoin(dir_name, filename));
}

void	print_type_n_rights(struct dirent *file, struct stat *file_stats,
																char *dir_name)
{
	char	buf[1025];

	if (file->d_type == DT_DIR)
		ft_putchar('d');
	else if (file->d_type == DT_LNK || (file->d_type == 0 && readlink(make_path(file->d_name, dir_name), buf, 1024) && errno == 0))
		ft_putchar('l');
	else
		ft_putchar('-');
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
}

void	print_nb_hlinks(struct stat *file_stats, int largest)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(ft_ntoa_base(file_stats->st_nlink, "0123456789"));
	while (i < largest - len + 2)
	{
		ft_putchar(' ');
		i++;
	}
	ft_printf("%lld", file_stats->st_nlink);
}

void	update_largest(int largest[6], struct stat *stats)
{
	long long	tmp;

	tmp = ft_strlen(ft_ntoa_base(stats->st_nlink, "0123456789"));
	if (tmp > largest[0])
		largest[0] = tmp;
	tmp = ft_strlen(getpwuid(stats->st_uid)->pw_name);
	if (tmp > largest[1])
		largest[1] = tmp;
	tmp = ft_strlen(getgrgid(stats->st_gid)->gr_name);
	if (tmp > largest[2])
		largest[2] = tmp;
	tmp = ft_strlen(ft_ntoa_base(stats->st_size, "0123456789"));
	if (tmp > largest[3])
		largest[3] = tmp;
}

struct stat	**get_file_stats(struct dirent **children, char *dir_name,
														int largest[6], int nb)
{
	int			i;
	struct stat	**res;
	char		buf[1025];

	if (!(res = (struct stat**)malloc(sizeof(struct stat*) * (nb + 1))))
		return (unexpected_error_null());
	res[nb] = NULL;
	i = 0;
	while (i < 4)
	{
		largest[i] = 0;
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (!(res[i] = (struct stat*)malloc(sizeof(struct stat))))
			return (unexpected_error_null());
		if (children[i]->d_type == DT_LNK || (children[i]->d_type == 0 && readlink(make_path(children[i]->d_name, dir_name), buf, 1024) && errno == 2))
			lstat(make_path(children[i]->d_name, dir_name), res[i]);
		else
			stat(make_path(children[i]->d_name, dir_name), res[i]);
		update_largest(largest, res[i]);
		i++;
	}
	return (res);
}

void	print_file_owner(struct stat *file_stats, int largest)
{
	int		i;
	int		len;
	char	*user;

	i = 0;
	user = getpwuid(file_stats->st_uid)->pw_name;
	len = ft_strlen(user);
	ft_putchar(' ');
	ft_putstr(user);
	while (i < largest - len)
	{
		ft_putchar(' ');
		i++;
	}
}

void	print_file_size(struct stat *file_stats, int largest)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(ft_ntoa_base(file_stats->st_size, "0123456789"));
	while (i < largest - len + 2)
	{
		ft_putchar(' ');
		i++;
	}
	ft_printf("%lld", file_stats->st_size);
}

void	print_group_name(struct stat *file_stats, int largest)
{
	int		i;
	int		len;
	char	*group;

	i = 0;
	group = getgrgid(file_stats->st_gid)->gr_name;
	len = ft_strlen(group);
	while (i < largest - len + 2)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putstr(group);
}

int		month_to_int(char *month)
{
	if (ft_strcmp(month, "Jan") == 0)
		return (1);
	if (ft_strcmp(month, "Feb") == 0)
		return (2);
	if (ft_strcmp(month, "Mar") == 0)
		return (3);
	if (ft_strcmp(month, "Apr") == 0)
		return (4);
	if (ft_strcmp(month, "Mai") == 0)
		return (5);
	if (ft_strcmp(month, "Jun") == 0)
		return (6);
	if (ft_strcmp(month, "Jul") == 0)
		return (7);
	if (ft_strcmp(month, "Aug") == 0)
		return (8);
	if (ft_strcmp(month, "Sep") == 0)
		return (9);
	if (ft_strcmp(month, "Oct") == 0)
		return (10);
	if (ft_strcmp(month, "Nov") == 0)
		return (11);
	if (ft_strcmp(month, "Dec") == 0)
		return (12);
	return (-1);
}

int		more_or_less_than_six_months(char **date)
{
	char	**current_date;
	int		dat[3];
	int		current_dat[3];
	long	crt;

	crt = time(NULL);
	current_date = ft_strsplit(ctime(&crt), ' ');
	current_dat[0] = ft_atoi(current_date[4]);
	current_dat[1] = month_to_int(current_date[1]);
	current_dat[2] = ft_atoi(current_date[2]); 
	dat[0] = ft_atoi(date[4]);
	dat[1] = month_to_int(date[1]);
	dat[2] = ft_atoi(date[2]);
	if (current_dat[0] - dat[0] < -1 || current_dat[0] - dat[0] > 1)
		return (1);
	if (current_dat[0] > dat[0])
		current_dat[1] += 12;
	else if (current_dat[0] < dat[0])
		dat[1] += 12;
	if (current_dat[1] - dat[1] < -6 || current_dat[1] - dat[1] > 6)
		return (1);
	if (current_dat[1] - dat[1] == 6 && current_dat[2] - dat[2] >= 0)
		return (1);
	if (current_dat[1] - dat[1] == -6 && current_dat[2] - dat[2] <= 0)
		return (1);
	return (0);
}

void	print_until_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	str[i] = '\0';
	ft_putstr(str);
}

void	print_date(struct stat *file_stats)
{
	char	**date;
	char	**hour;

	date = ft_strsplit(ctime(&file_stats->st_mtimespec.tv_sec), ' ');
	ft_putchar(' ');
	ft_putstr(date[1]);
	ft_putchar(' ');
	if (ft_strlen(date[2]) == 1)
		ft_putchar(' ');
	ft_putstr(date[2]);
	if (more_or_less_than_six_months(date))
	{
		ft_putstr("  ");
		print_until_newline(date[4]);
	}
	else
	{
		hour = ft_strsplit(date[3], ':');
		ft_putchar(' ');
		ft_putstr(hour[0]);
		ft_putchar(':');
		ft_putstr(hour[1]);
	}
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

int		print_children_details(struct dirent **children, t_flags *flags,
														int nb, char *dir_name)
{
	int			i;
	struct stat	**file_stats;
	int			largest[4];
	char		buf[1025];

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
		print_file_size(file_stats[i], largest[3]);
		print_date(file_stats[i]);
		ft_putchar(' ');
		ft_putstr(children[i]->d_name);
		if (children[i]->d_type == DT_LNK || (children[i]->d_type == 0 && readlink(make_path(children[i]->d_name, dir_name), buf, 1024) && errno == 0))
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

int		ft_strcmp_child_name(void *elt1, void *elt2, void *elt3)
{
	(void)elt3;
	return (-ft_strcmp(((struct dirent*)elt1)->d_name,
											((struct dirent*)elt2)->d_name));
}

int		compare_by_date(void *elt1, void *elt2, void *elt3)
{
	static struct stat		*stat1 = NULL;
	long					date1;

	if (!stat1)
		stat1 = (struct stat*)malloc(sizeof(struct stat));
	if (((struct dirent*)elt1)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt1)->d_name, (char*)elt3), stat1);
	date1 = (long)stat1->st_mtimespec.tv_sec;
	if (((struct dirent*)elt2)->d_type == DT_LNK)
		lstat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	else
		stat(make_path(((struct dirent*)elt2)->d_name, (char*)elt3), stat1);
	if (date1 != (long)stat1->st_mtimespec.tv_sec)
		return (date1 - (long)stat1->st_mtimespec.tv_sec);
	return (ft_strcmp_child_name(elt1, elt2, NULL));
}

void	sort_by_name(struct dirent **children, int nb)
{
	quicksort((void**)children, nb, ft_strcmp_child_name, NULL);
}

void	sort_by_date(struct dirent **children, int nb, char *dir_name)
{
	quicksort((void**)children, nb, compare_by_date, (void*)dir_name);
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
		sort_by_date(children, nb_child, dir_name);
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

char	*add_dir_name(char *filename, char *dir_name)
{
	return (ft_strjoin(ft_strjoin(dir_name, "/"), filename));
}

void	add_file_to_dir_children(struct dirent *tmp_child, t_flags *flags,
										t_list **dir_children, char *dir_name)
{
	t_list	*new_elt;
	char	*dir_name_added;

	if (tmp_child->d_type == DT_DIR
		&& ft_strcmp(tmp_child->d_name, ".") != 0
		&& ft_strcmp(tmp_child->d_name, "..") != 0
		&& (flags->a || tmp_child->d_name[0] != '.'))
	{
		dir_name_added = add_dir_name(tmp_child->d_name, dir_name);
		new_elt = ft_lstnew(dir_name_added,
						sizeof(char) * (ft_strlen(dir_name_added) + 1));
		ft_lstaddend(dir_children, new_elt);
	}
}

int		listdir(DIR *dir, t_flags *flags, char *dir_name, t_list *dir_children)
{
	struct dirent	*tmp_child;
	t_list			*children_list;
	t_list			*child_lst_n;
	struct dirent	**children;
	int				length;

	length = 0;
	children_list = NULL;
	child_lst_n = NULL;
	while ((tmp_child = readdir(dir)))
	{
		if (tmp_child->d_name[0] != '.' || flags->a)
		{
			ft_lstaddend(&child_lst_n, ft_lstnew(tmp_child, sizeof(struct dirent)));
			if (!children_list)
				children_list = child_lst_n;
			length++;
		}
		add_file_to_dir_children(tmp_child, flags, &dir_children, dir_name);
	}
	if (!(children = children_list_to_array(children_list, length)))
		return (unexpected_error());
	print_children(children, flags, length, dir_name);
	return (1);
}

void	file_error(char *filename)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putendl_fd(": No such file or directory\n", 2);
}

char	**list_to_string_array(t_list *params)
{
	int		length;
	t_list	*tmp;
	char	**res;

	tmp = params;
	length = 0;
	while (tmp)
	{
		tmp = tmp->next;
		length++;
	}
	if (!(res = (char**)malloc(sizeof(char*) * (length + 1))))
		return (NULL);
	res[length] = NULL;
	length = 0;
	while (params)
	{
		res[length] = (char*)params->content;
		tmp = params;
		params = params->next;
		free(tmp);
		length++;
	}
	return (res);
}

void	add_to_lists(int error, t_list **params, t_list **other_params,
																	char *str)
{
	if (error == -1)
	{
		if (!*params)
			ft_lstaddend(params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
		else
			ft_lstadd(params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
	}
	else if (error == ENOTDIR)
	{
		if (!*other_params)
			ft_lstaddend(other_params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
		else
			ft_lstadd(other_params,
						ft_lstnew(str, sizeof(char) * (ft_strlen(str) + 1)));
	}
	else
		print_errno(error, str);
}

char	**get_params(int argc, char **argv, int i, t_list **other_params)
{
	t_list		*params;
	DIR			*tmp;
	int			error;
	struct stat	*stats;

	params = NULL;
	if (!(stats = (struct stat*)malloc(sizeof(struct stat))))
		return (NULL);
	if (i == argc)
		ft_lstaddend(&params, ft_lstnew(".", sizeof(char) * 2));
	else
	{
		while (i < argc)
		{
			error = -1;
			if (!(tmp = opendir(argv[i])))
			{
				error = errno;
				if (error == ENOENT && !(lstat(argv[i], stats)))
					error = ENOTDIR;
				if (error != ENOTDIR)
					print_errno(error, argv[i]);
			}
			if (error == -1 || error == ENOTDIR)
			{
				if (error == -1 && closedir(tmp) == -1)
					error = errno;
				add_to_lists(error, &params, other_params, argv[i]);
			}
			i++;
		}
	}
	return (list_to_string_array(params));
}

int		strstrlen(char **strstr)
{
	int		i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

struct dirent	**strstr_to_dirent_array(char **params, int *l)
{
	struct dirent	**children;
	int				i;

	*l = 0;
	while (params[*l])
		(*l)++;
	if (*l <= 0)
		return (NULL);
	if (!(children = (struct dirent**)malloc(sizeof(struct dirent*) * (*l + 1))))
		return (unexpected_error_null());
	i = 0;
	while (i < *l)
	{
		if (!(children[i] = (struct dirent*)malloc(sizeof(struct dirent))))
			return (unexpected_error_null());
		ft_strcpy(children[i]->d_name, params[i]);
		i++;
	}
	return (children);
}

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
		sort_by_date(dirs, l, NULL);
	else
		sort_by_name(dirs, l);
	if (flags->r)
		reverse_children(dirs, l);
}

int		print_dir_params(char **dir_params, t_flags *flags,
										char **other_params, char print_name)
{
	DIR				*tmp_dir;
	struct dirent	**dirs;
	int				i;
	int				l;
	t_list			*dir_children;

	if (!(dirs = strstr_to_dirent_array(dir_params, &l)))
		return (0);
	order_dirs(dirs, flags, l);
	i = 0;
	while (i < l)
	{
		if (i != 0)
			ft_putchar('\n');
		if (i != 0 || (other_params && other_params[0]) || i + 1 < l || print_name)
		{
			ft_putstr(dirs[i]->d_name);
			ft_putendl(":");
		}
		if ((tmp_dir = opendir(dirs[i]->d_name)))
		{
			dir_children = ft_lstnew(NULL, 0);
			listdir(tmp_dir, flags, dirs[i]->d_name, dir_children);
			closedir(tmp_dir);
			if (flags->r_maj && dir_children->next)
			{
				ft_putchar('\n');
				print_dir_params(list_to_string_array(dir_children->next), flags, NULL, 1);
			}
		}
		else
			print_errno(errno, dirs[i]->d_name);
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

int		ft_strcmp_void(void *elt1, void *elt2, void *elt3)
{
	(void)elt3;
	return (-ft_strcmp((char*)elt1, (char*)elt2));
}

void	sort_args(int argc, char **argv, int i)
{
	if (argc - i <= 1)
		return ;
	quicksort((void**)(argv + i), argc - i, ft_strcmp_void, NULL);
}

int		found_void_param(int argc, char **argv, int i)
{
	while (i < argc)
	{
		if (ft_strlen(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_flags			*flags;
	char			**dir_params;
	char			**other_params;
	t_list			**other_params_list;
	int				i;

	if (!(other_params_list = (t_list**)malloc(sizeof(t_list*))))
		return (unexpected_error());
	*other_params_list = NULL;
	other_params = NULL;
	if (!(flags = get_flags(argc, argv, &i)))
		return (0);
	if (found_void_param(argc, argv, i))
	{
		print_errno(ENOENT, "");
		return (0);
	}
	sort_args(argc, argv, i);
	dir_params = get_params(argc, argv, i, other_params_list);
	if (other_params_list)
		other_params = list_to_string_array(*other_params_list);
	return (print_params(dir_params, other_params, flags, argc - i));
}
