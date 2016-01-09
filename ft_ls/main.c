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

int		illegal_option(char c)
{
	char	*str;

	str = "ft_ls: illegal option -- %c\nusage: ft_ls [-lRart] [file ...]\n";
	ft_printf(str, c);
	return (0);
}

int		unexpected_error(void)
{
	ft_putendl_fd("ft_ls: unexpected error", 2);
	return (0);
}

int		set_flag(char c, t_flags *flags)
{
	if (c == 'l')
		flags->l = 1;
	else if (c == 'R')
		flags->r_maj = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 'a')
		flags->a = 1;
	else if (c == 't')
		flags->t = 1;
	else
		return (0);
	return (1);
}

t_flags	*void_flags(void)
{
	t_flags	*res;

	if (!(res = (t_flags*)malloc(sizeof(t_flags))))
		return (NULL);
	res->a = 0;
	res->r = 0;
	res->r_maj = 0;
	res->l = 0;
	res->t = 0;
	return (res);
}

int		add_flags(char *arg, t_flags *flags)
{
	int		i;

	if (arg[0] != '-' || !arg[1])
		flags->dir = opendir(arg);
	else
	{
		i = 1;
		while (arg[i])
		{
			if (!set_flag(arg[i], flags))
				return (illegal_option(arg[i]));
			i++;
		}
	}
	return (1);
}

t_flags	*get_flags(int argc, char **argv)
{
	t_flags	*res;
	int		i;

	res = void_flags();
	if (!res)
		return (NULL);
	res->dir = opendir(".");
	i = 1;
	while (i < argc)
	{
		if (!(add_flags(argv[i], res)))
			return (NULL);
		i++;
	}
	return (res);
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

int		get_largest_child(struct dirent **children)
{
	int		i;
	int		largest;

	i = 0;
	largest = -1;
	while (children[i])
	{
		if (children[i]->d_namlen > largest)
			largest = children[i]->d_namlen;
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

int		print_children_regular(struct dirent **children, int nb)
{
	int				i;
	int				x;
	int				largest;
	int				nb_per_line;
	int				nb_lines;
	struct winsize	*w;

	largest = get_largest_child(children);
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
			ft_putstr(children[i * nb_lines + x]->d_name);
			if (i + 1 < nb_per_line && (i + 1) * nb_lines + x < nb)
				print_n_tabs((largest - children[i * nb_lines + x]->d_namlen + 8) / 8);
			i++;
		}
		ft_putchar('\n');
		x++;
	}
	return (1);
}

void	sort_by_date(struct dirent **children)
{
	(void)children;
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

void	print_children(struct dirent **children, t_flags *flags, int nb_child)
{
	if (flags->t)
		sort_by_date(children);
	if (flags->r)
		reverse_children(children, nb_child);
	if (flags->l)
		print_children_details(children, flags);
	else
		print_children_regular(children, nb_child);
}

int		listdir(DIR *dir, t_flags *flags)
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
	print_children(children, flags, length);
	return (1);
}

int		main(int argc, char **argv)
{
	t_flags			*flags;

	if (!(flags = get_flags(argc, argv)))
		return (0);
	listdir(flags->dir, flags);
	return (0);
}
