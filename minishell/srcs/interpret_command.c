/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:40:19 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:40:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_strstr(char **strstr)
{
	size_t	i;

	i = 0;
	while (strstr[i])
	{
		ft_putstr(strstr[i]);
		ft_putstr("\n");
		i++;
	}
}

char	*get_home(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'H' && env[i][1] == 'O' && env[i][2] == 'M'
			&& env[i][3] == 'E' && env[i][4] == '=')
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (ft_strdup("/"));
}

char	*replace_tilde_str(char *home, size_t home_len, char *line)
{
	size_t	line_len;
	size_t	i;
	char	*res;

	line_len = ft_strlen(line) - 1;
	if (!(res = (char*)malloc(sizeof(char) * (home_len + line_len + 1))))
		malloc_error();
	res[home_len + line_len] = '\0';
	i = 0;
	while (home[i])
	{
		res[i] = home[i];
		i++;
	}
	line_len = 1;
	while (line[line_len])
	{
		res[i + line_len - 1] = line[line_len];
		line_len++;
	}
	return (res);
}

void	handle_dollar(char **line, size_t i, char **env)
{
	char	*value;

	value = get_env_var(line[i] + 1, env);
	if (!value)
		return ;
	free(line[i]);
	line[i] = value;
}

void	replace_tilde(char **line, char **env)
{
	size_t	i;
	char	*tmp;
	char	*home;
	size_t	len;

	home = get_env_var("HOME", env);
	if (!home)
		return ;
	len = ft_strlen(home);
	if (home[len - 1] == '/')
		home[len - 1] = '\0';
	i = 0;
	while (line[i])
	{
		if (line[i][0] == '~' && (!line[i][1] || line[i][1] == '/'))
		{
			tmp = replace_tilde_str(home, len, line[i]);
			free(line[i]);
			line[i] = tmp;
		}
		else if (line[i][0] == '$')
			handle_dollar(line, i, env);
		i++;
	}
}
