/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:22:28 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 16:22:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_linked_list *list)
{
	int		i;

	i = 0;
	while (i < list->len)
	{
		ft_putstr(list->elts[i]);
		ft_putstr("\n");
		i++;
	}
}

void	get_files_in_dir(char *path, t_linked_list *files, char dirs,
															char not_exec)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp_full_path;
	struct stat		file_stat;

	if (!(dir = opendir(path)))
		return ;
	while ((file = readdir(dir)))
	{
		tmp_full_path = build_file_path(path, file->d_name);
		if (stat(tmp_full_path, &file_stat) != -1)
		{
			if (dirs || !S_ISDIR(file_stat.st_mode))
			{
				if (not_exec
					|| (access(tmp_full_path, X_OK) != -1 && dirs != 2))
					add_to_list(files, ft_strdup(file->d_name));
			}
		}
		free(tmp_full_path);
	}
	closedir(dir);
}

char	*get_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}
