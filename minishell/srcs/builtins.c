/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:39:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:39:26 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(char **line, char ***env)
{
	size_t	i;
	char	found;
	char	**new_env;

	found = get_found(line, env, &i);
	if (!found)
		return ;
	if (!(new_env = (char**)malloc(sizeof(char*) * i)))
		malloc_error();
	new_env[i - 1] = NULL;
	i = 0;
	found = 0;
	while ((*env)[i])
	{
		if (!(startswith(line[1], (*env)[i])))
			new_env[i - found] = (*env)[i];
		else
			found = 1;
		i++;
	}
	free(*env);
	*env = new_env;
}

void	set_old_pwd(char ***env)
{
	char	*path;
	char	**line;

	path = get_current_path();
	if (!(line = (char**)malloc(sizeof(char*) * 4)))
		malloc_error();
	line[3] = NULL;
	line[0] = ft_strdup("env");
	line[1] = ft_strdup("OLDPWD");
	line[2] = path;
	set_env(line, env);
	free(line[0]);
	free(line[1]);
	free(line[2]);
	free(line);
}

void	set_new_pwd(char ***env)
{
	char	*path;
	char	**line;

	path = get_current_path();
	if (!(line = (char**)malloc(sizeof(char*) * 4)))
		malloc_error();
	line[3] = NULL;
	line[0] = ft_strdup("env");
	line[1] = ft_strdup("PWD");
	line[2] = path;
	set_env(line, env);
	free(line[0]);
	free(line[1]);
	free(line[2]);
	free(line);
}

void	change_dir(char *dir_path, char ***env)
{
	struct stat	file;

	if (stat(dir_path, &file) == -1)
	{
		ft_putstr("minishell: ");
		ft_putstr(dir_path);
		ft_putstr(": No such file or directory\n");
	}
	else if (S_ISDIR(file.st_mode))
	{
		set_old_pwd(env);
		chdir(dir_path);
		set_new_pwd(env);
	}
	else
	{
		ft_putstr("minishell: ");
		ft_putstr(dir_path);
		ft_putstr(": Not a directory\n");
	}
}

void	handle_builtin(char **line, char ***env)
{
	if (ft_strcmp(line[0], "env") == 0)
		print_strstr(*env);
	else if (ft_strcmp(line[0], "setenv") == 0 && line[1]
		&& line[2] && !char_in_str(line[1], '='))
		set_env(line, env);
	else if (ft_strcmp(line[0], "unsetenv") == 0 && line[1]
		&& !char_in_str(line[1], '='))
		unset_env(line, env);
	else if (ft_strcmp(line[0], "exit") == 0)
	{
		ft_putstr("bye\n");
		exit(0);
	}
	else if (ft_strcmp(line[0], "cd") == 0)
	{
		if (!line[1])
			change_dir(get_home(*env), env);
		else
			change_dir(line[1], env);
	}
}
