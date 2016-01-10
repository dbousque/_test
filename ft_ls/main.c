/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:59:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/09 18:44:03 by dbousque         ###   ########.fr       */
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

int		next_tab(int largest)
{
	return (largest + 8 - largest % 8);
}

int		get_largest_string(char **strings)
{
	int		i;
	int		largest;

	i = 0;
	largest = -1;
	while (strings[i])
	{
		if ((int)ft_strlen(strings[i]) > largest)
			largest = (int)ft_strlen(strings[i]);
		i++;
	}
	return (next_tab(largest));
}

void	print_children_details(struct dirent **children, t_flags *flags)
{
	(void)flags;
	(void)children;
}

void	print_n_tabs(int n)
{
	while (n > 0)
	{
		ft_putstr("\t");
		n--;

	}
}

int		print_string_array_columns(char **strings, int nb)
{
	int				i;
	int				x;
	int				largest;
	int				nb_per_line;
	int				nb_lines;
	struct winsize	*w;

	largest = get_largest_string(strings);
	if (!(w = (struct winsize*)malloc(sizeof(struct winsize))))
		return (0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
	nb_per_line = w->ws_col / largest + 1;
	nb_lines = nb / nb_per_line + 1;
	x = 0;
	while (x < nb_lines && x < nb)
	{
		i = 0;
		while (i < nb_per_line && i * nb_lines + x < nb)
		{
			ft_putstr(strings[i * nb_lines + x]);
			if (i + 1 < nb_per_line && (i + 1) * nb_lines + x < nb)
				print_n_tabs((largest - ft_strlen(strings[i * nb_lines + x]) + 8) / 8);
			i++;
		}
		ft_putchar('\n');
		x++;
	}
	return (1);
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

	(void)nb;
	i = 0;
	while (children[i])
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
		print_children_details(children, flags);
	else if (flags->minus)
		print_children_regular_std(children, nb_child);
	else
		print_children_regular(children, nb_child);
}

int		listdir(DIR *dir, t_flags *flags, char *dir_name)
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

void	print_errno(int error, char *filename)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(error), 2);
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
	t_list	*params;
	DIR		*tmp;
	int		error;

	params = NULL;
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

int		print_dir_params(char **dir_params, t_flags *flags, char **other_params)
{
	DIR				*tmp_dir;
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
		if (i != 0 || other_params[0] || i + 1 < l)
		{
			ft_putstr(dirs[i]->d_name);
			ft_putendl(":");
		}
		tmp_dir = opendir(dirs[i]->d_name);
		listdir(tmp_dir, flags, dirs[i]->d_name);
		closedir(tmp_dir);
		i++;
	}
	return (1);
}

int		print_params(char **dir_params, char **other_params, t_flags *flags)
{
	int		res;

	res = print_other_params(other_params, flags);
	if (res == 2 && dir_params[0])
		ft_putchar('\n');
	print_dir_params(dir_params, flags, other_params);
	return (0);
}

int		ft_strcmp_void(void *elt1, void *elt2, void *elt3)
{
	(void)elt3;
	return (ft_strcmp((char*)elt1, (char*)elt2));
}

void	sort_args(int argc, char **argv, int i)
{
	if (argc - i <= 1)
		return ;
	quicksort((void**)(argv + i), argc - i, ft_strcmp_void, NULL);
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
	//sort_args(argc, argv, i);
	dir_params = get_params(argc, argv, i, other_params_list);
	if (other_params_list)
		other_params = list_to_string_array(*other_params_list);
	return (print_params(dir_params, other_params, flags));
}
