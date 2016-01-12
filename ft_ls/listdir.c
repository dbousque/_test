/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:26:10 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 18:29:52 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

char			*add_dir_name(char *filename, char *dir_name)
{
	return (ft_strjoin(ft_strjoin(dir_name, "/"), filename));
}

void			add_file_to_dir_children(struct dirent *tmp_child,
					t_flags *flags, t_list **dir_children, char *dir_name)
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

int				listdir(DIR *dir, t_flags *flags, char *dir_name,
														t_list *dir_children)
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
			ft_lstaddend(&child_lst_n,
								ft_lstnew(tmp_child, sizeof(struct dirent)));
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
