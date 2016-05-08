/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:41:07 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:41:09 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	escaped_char(char *str, int i)
{
	int		nb;

	nb = 0;
	i--;
	while (i >= 0)
	{
		if (str[i] == '\\')
			nb++;
		else
			break ;
		i--;
	}
	if (nb % 2 == 1)
		return (1);
	return (0);
}

void	handle_quote(t_linked_list *args, char *command, t_ind *ind,
															char *in_str)
{
	if (*in_str)
	{
		if (*in_str == command[ind->i])
		{
			if (!escaped_char(command, ind->i))
			{
				*in_str = 0;
				if (ignore_char(command[ind->i + 1]))
				{
					add_string_to_args(args, command, ind->start, ind->i);
					ind->start = ind->i + 1;
				}
			}
		}
	}
	else
		*in_str = command[ind->i];
}

char	**list_to_args(t_linked_list *args)
{
	char	**res;
	int		i;

	if (!(res = (char**)malloc(sizeof(char*) * (args->len + 1))))
		malloc_error();
	res[args->len] = NULL;
	i = 0;
	while (i < args->len)
	{
		res[i] = args->elts[i];
		i++;
	}
	free(args->elts);
	free(args);
	return (res);
}

void	split_command_in_args2(char *command, t_linked_list *args, t_ind *ind,
																char *in_str)
{
	if (!*in_str && (ignore_char(command[ind->i]) || command[ind->i] == ';'))
	{
		if (ind->start != ind->i)
			add_string_to_args(args, command, ind->start, ind->i);
		if (command[ind->i] == ';')
			add_to_list(args, ft_strdup(";"));
		ind->start = ind->i + 1;
	}
	else if (command[ind->i] == '"' || command[ind->i] == '\'')
		handle_quote(args, command, ind, in_str);
}

char	**split_command_in_args(char *command)
{
	t_linked_list	*args;
	t_ind			ind;
	char			in_str;

	args = new_list();
	ind.i = 0;
	while (command[ind.i] && ignore_char(command[ind.i]))
		ind.i++;
	if (!command[ind.i])
		return (NULL);
	ind.start = ind.i;
	in_str = 0;
	while (command[ind.i])
	{
		split_command_in_args2(command, args, &ind, &in_str);
		ind.i++;
	}
	if (ind.start != ind.i)
		add_string_to_args(args, command, ind.start, ind.i);
	return (list_to_args(args));
}
