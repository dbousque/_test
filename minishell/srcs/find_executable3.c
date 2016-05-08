/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:22:37 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 16:22:40 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_linked_list	*get_files_from_path(char **env)
{
	t_linked_list	*dirs;
	t_dir			*tmp_dir;
	char			**paths;
	char			*path;
	size_t			i;

	path = get_path(env);
	if (!path)
		return (NULL);
	paths = ft_strsplit(path, ':');
	dirs = new_list();
	i = 0;
	while (paths[i])
	{
		if (!(tmp_dir = (t_dir*)malloc(sizeof(t_dir))))
			malloc_error();
		tmp_dir->files = new_list();
		tmp_dir->path = ft_strdup(paths[i]);
		get_files_in_dir(paths[i], tmp_dir->files, 0, 0);
		add_to_list(dirs, tmp_dir);
		i++;
	}
	free_ptrptr((void**)paths);
	return (dirs);
}

void			get_files_from_path2(char **env, t_linked_list *files)
{
	char			**paths;
	char			*path;
	size_t			i;

	path = get_path(env);
	if (!path)
		return ;
	paths = ft_strsplit(path, ':');
	i = 0;
	while (paths[i])
	{
		get_files_in_dir(paths[i], files, 0, 0);
		i++;
	}
	free_ptrptr((void**)paths);
}

char			*build_file_path2(char *dir_path, char *file_name,
											char *res, char add_slash)
{
	size_t	i;
	size_t	name_len;

	i = 0;
	while (dir_path[i])
	{
		res[i] = dir_path[i];
		i++;
	}
	name_len = i + add_slash;
	if (add_slash)
		res[i] = '/';
	i = 0;
	while (file_name[i])
	{
		res[name_len + i] = file_name[i];
		i++;
	}
	return (res);
}

char			*build_file_path(char *dir_path, char *file_name)
{
	size_t	i;
	size_t	name_len;
	char	*res;
	char	add_slash;

	name_len = ft_strlen(file_name);
	add_slash = 1;
	i = 0;
	while (dir_path[i])
		i++;
	if (i == 0 || dir_path[i - 1] == '/')
		add_slash = 0;
	if (!(res = (char*)malloc(sizeof(char) * (i + add_slash + name_len + 1))))
		malloc_error();
	res[i + add_slash + name_len] = '\0';
	return (build_file_path2(dir_path, file_name, res, add_slash));
}

char			file_in_list(char *file, t_linked_list *files)
{
	int		i;

	i = 0;
	while (i < files->len)
	{
		if (ft_strcmp(file, files->elts[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
