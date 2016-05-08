/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:22:46 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 16:22:48 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_exec_from_path(char *prog, t_linked_list *dirs)
{
	int		i;

	i = 0;
	while (i < dirs->len)
	{
		if (file_in_list(prog, ((t_dir*)dirs->elts[i])->files))
			return (build_file_path(((t_dir*)dirs->elts[i])->path, prog));
		i++;
	}
	return (NULL);
}

char	*find_exec_current_dir(char *prog)
{
	return (prog);
}

void	command_not_found(char *command)
{
	ft_putstr(command);
	ft_putstr(": command not found\n");
}

char	char_in_str(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
