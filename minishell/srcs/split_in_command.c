/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:41:27 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:41:29 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_elts(char **elts)
{
	size_t	i;

	i = 0;
	while (elts[i] && ft_strcmp(elts[i], ";") != 0)
		i++;
	return (i);
}

char	***split_in_commands2(char ***commands, char **line, size_t count,
																	size_t i)
{
	size_t	ind;
	size_t	x;
	size_t	count2;

	ind = 0;
	x = 0;
	while (ind < count + 1)
	{
		count2 = count_elts(line + x);
		if (!(commands[ind] = (char**)malloc(sizeof(char*) * (count2 + 1))))
			malloc_error();
		commands[ind][count2] = NULL;
		i = 0;
		while (i < count2)
		{
			commands[ind][i] = line[x];
			x++;
			i++;
		}
		x++;
		ind++;
	}
	return (commands);
}

char	***split_in_commands(char **line)
{
	size_t	i;
	int		count;
	char	***commands;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (ft_strcmp(line[i], ";") == 0)
			count++;
		i++;
	}
	if (!(commands = (char***)malloc(sizeof(char**) * (count + 2))))
		malloc_error();
	commands[count + 1] = NULL;
	return (split_in_commands2(commands, line, count, 0));
}

void	print_commands(char ***commands)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (commands[y])
	{
		ft_putstr("NEW INSTR\n\n");
		x = 0;
		while (commands[y][x])
		{
			ft_putstr(commands[y][x]);
			ft_putstr("|\n");
			x++;
		}
		y++;
	}
}
