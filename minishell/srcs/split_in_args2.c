/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_args2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:41:16 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:41:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ignore_char(char c)
{
	if (c == ' ' || (c <= 31 && c >= 0) || c >= 127)
		return (1);
	return (0);
}

void	add_string_to_args2(char *command, char *to_add, t_vars *vars,
															char *in_str)
{
	if (!(command[vars->start + vars->x] == '"'
		|| command[vars->start + vars->x] == '\''))
	{
		to_add[vars->i] = command[vars->start + vars->x];
		vars->i++;
	}
	else
	{
		if (!*in_str)
			*in_str = command[vars->start + vars->x];
		else
		{
			if (command[vars->start + vars->x] == *in_str)
				*in_str = 0;
			else
			{
				to_add[vars->i] = command[vars->start + vars->x];
				vars->i++;
			}
		}
	}
}

void	add_string_to_args(t_linked_list *args, char *command, size_t start,
																size_t end)
{
	char	*to_add;
	t_vars	vars;
	char	in_str;

	vars.start = start;
	in_str = 0;
	if (!(to_add = (char*)malloc(sizeof(char) * (end - vars.start + 1))))
		malloc_error();
	vars.i = 0;
	vars.x = 0;
	while (vars.x < end - vars.start)
	{
		if (command[vars.start + vars.x] == '\\')
		{
			to_add[vars.i] = command[vars.start + vars.x + 1];
			vars.x++;
			vars.i++;
		}
		else
			add_string_to_args2(command, to_add, &vars, &in_str);
		vars.x++;
	}
	to_add[vars.i] = '\0';
	add_to_list(args, to_add);
}

void	reload_env(char ***old_env)
{
	if (*old_env)
		free_ptrptr((void**)*old_env);
	*old_env = copy_environ();
}

void	ctrl_c(int id)
{
	(void)id;
	ft_putstr("\n");
}
