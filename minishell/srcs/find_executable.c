/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:07:11 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 16:07:13 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*no_such_file_or_dir(char *prog)
{
	ft_putstr("minishell: ");
	ft_putstr(prog);
	ft_putstr(": No such file or directory\n");
	return (NULL);
}

char	*is_a_dir(char *prog)
{
	ft_putstr("minishell: ");
	ft_putstr(prog);
	ft_putstr(": Is a directory\n");
	return (NULL);
}

char	*permission_denied(char *prog)
{
	ft_putstr("minishell: ");
	ft_putstr(prog);
	ft_putstr(": Permission denied\n");
	return (NULL);
}

char	*find_exec_with_path(char *prog)
{
	struct stat	file;

	if (stat(prog, &file) == -1)
		return (no_such_file_or_dir(prog));
	if (S_ISDIR(file.st_mode))
		return (is_a_dir(prog));
	if (access(prog, X_OK) == -1)
		return (permission_denied(prog));
	return (prog);
}

char	*find_executable(char *prog, char **env)
{
	t_linked_list	*files;
	char			*exec;

	exec = NULL;
	if (char_in_str(prog, '/'))
		exec = find_exec_with_path(prog);
	else
	{
		files = get_files_from_path(env);
		if (files)
			exec = find_exec_from_path(prog, files);
		if (!exec)
		{
			command_not_found(prog);
			return (NULL);
		}
	}
	return (exec);
}
