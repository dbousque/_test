/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:40:25 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:40:27 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_environ;

char	*get_env_var(char *key, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (startswith(key, env[i]))
			return (env[i] + ft_strlen(key) + 1);
		i++;
	}
	return (NULL);
}

char	*get_logname(char **env)
{
	char	*tmp;

	tmp = get_env_var("LOGNAME", env);
	if (!tmp)
		tmp = get_env_var("USER", env);
	return (tmp);
}

size_t	ptrptrlen(void **ptrptr)
{
	size_t	i;

	i = 0;
	while (ptrptr[i])
		i++;
	return (i);
}

void	free_ptrptr(void **ptrptr)
{
	size_t	i;

	i = 0;
	while (ptrptr[i])
	{
		free(ptrptr[i]);
		i++;
	}
	free(ptrptr);
}

char	**copy_environ(void)
{
	int		len;
	char	**env;
	size_t	str_len;
	int		i;
	size_t	x;

	len = ptrptrlen((void**)g_environ);
	if (!(env = (char**)malloc(sizeof(char*) * (len + 1))))
		malloc_error();
	env[len] = NULL;
	i = -1;
	while (++i < len)
	{
		str_len = ft_strlen(g_environ[i]);
		if (!(env[i] = (char*)malloc(sizeof(char) * (str_len + 1))))
			malloc_error();
		env[i][str_len] = '\0';
		x = 0;
		while (x < str_len)
		{
			env[i][x] = g_environ[i][x];
			x++;
		}
	}
	return (env);
}
