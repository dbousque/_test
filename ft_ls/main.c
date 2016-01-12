/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 17:06:04 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

__uint8_t	get_d_type_from_stat(struct stat *stats)
{
	if (stats->st_mode & S_IFIFO)
		return (DT_FIFO);
	if (stats->st_mode & S_IFDIR)
		return (DT_DIR);
	if (stats->st_mode & S_IFREG)
		return (DT_REG);
	if (stats->st_mode & S_IFLNK)
		return (DT_LNK);
	if (stats->st_mode & S_IFCHR)
		return (DT_CHR);
	if (stats->st_mode & S_IFBLK)
		return (DT_BLK);
	if (stats->st_mode & S_IFSOCK)
		return (DT_SOCK);
	if (stats->st_mode & S_IFWHT)
		return (DT_WHT);
	return (DT_UNKNOWN);
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
													char *str, t_flags *flags)
{
	struct stat	*tmp_stat;

	if (!(tmp_stat = (struct stat*)malloc(sizeof(struct stat))))
		return ;
	lstat(str, tmp_stat);
	if (flags->l && get_d_type_from_stat(tmp_stat) != DT_DIR)
		error = ENOTDIR;
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

char	**get_params(int argc, char **argv, int i, t_list **other_params, t_flags *flags)
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
				add_to_lists(error, &params, other_params, argv[i], flags);
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
	if (argc - i < 400)
		quicksort((void**)(argv + i), argc - i, ft_strcmp_void, NULL);
	else
		insertion_sort((void**)(argv + i), argc - i, ft_strcmp_void, NULL);
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
	dir_params = get_params(argc, argv, i, other_params_list, flags);
	if (other_params_list)
		other_params = list_to_string_array(*other_params_list);
	return (print_params(dir_params, other_params, flags, argc - i));
}
