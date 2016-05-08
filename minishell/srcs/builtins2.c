/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:39:29 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:39:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	startswith(char *str, char *env)
{
	size_t	i;

	i = 0;
	while (str[i] && env[i])
	{
		if (str[i] != env[i])
			return (0);
		i++;
	}
	if (env[i] == '=')
		return (1);
	return (0);
}

char	*build_env_var(char *part1, char *part2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(part1);
	len2 = ft_strlen(part2);
	if (!(res = (char*)malloc(sizeof(char) * (len1 + len2 + 2))))
		malloc_error();
	res[len1 + len2 + 1] = '\0';
	len1 = 0;
	while (part1[len1])
	{
		res[len1] = part1[len1];
		len1++;
	}
	res[len1] = '=';
	len2 = 0;
	while (part2[len2])
	{
		res[len1 + 1 + len2] = part2[len2];
		len2++;
	}
	return (res);
}

char	set_env2(char **new_env, char **line, char ***env, size_t i)
{
	char	done;

	done = 0;
	if (startswith(line[1], (*env)[i]))
	{
		new_env[i] = build_env_var(line[1], line[2]);
		done = 1;
	}
	else
		new_env[i] = (*env)[i];
	return (done);
}

void	set_env(char **line, char ***env)
{
	char	**new_env;
	size_t	len;
	size_t	i;
	char	done;

	done = 0;
	len = strstrlen(*env);
	if (!(new_env = (char**)malloc(sizeof(char*) * (len + 2))))
		malloc_error();
	new_env[len + 1] = NULL;
	i = 0;
	while ((*env)[i])
	{
		if (set_env2(new_env, line, env, i))
			done = 1;
		i++;
	}
	new_env[i] = NULL;
	if (!done)
		new_env[i] = build_env_var(line[1], line[2]);
	free(*env);
	*env = new_env;
}

char	get_found(char **line, char ***env, size_t *i)
{
	char	found;

	found = 0;
	*i = 0;
	while ((*env)[*i])
	{
		if (startswith(line[1], (*env)[*i]))
			found = 1;
		(*i)++;
	}
	return (found);
}
