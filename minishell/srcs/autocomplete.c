/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:38:57 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 18:56:41 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_replace(char *res, size_t len, char *replace)
{
	size_t	i;

	i = 0;
	while (replace[i])
	{
		res[len] = replace[i];
		len++;
		i++;
	}
	res[len] = ' ';
	return (res);
}

void	add_removed(char *res, char *last, int nb_removed, size_t len)
{
	int		i;

	i = 0;
	while (i < nb_removed)
	{
		res[len] = last[i];
		len++;
		i++;
	}
}

char	*replace_end(char **parts, char *replace, int nb_removed)
{
	size_t	len;
	int		i;
	int		x;
	char	*res;

	len = get_len(parts);
	if (!(res = (char*)malloc(sizeof(char) *
					(len + ft_strlen(replace) + nb_removed + 2))))
		malloc_error();
	res[len + ft_strlen(replace) + nb_removed + 1] = '\0';
	i = -1;
	len = 0;
	while (parts[++i] && parts[i + 1])
	{
		x = -1;
		while (parts[i][++x])
		{
			res[len] = parts[i][x];
			len++;
		}
		res[len] = ' ';
		len++;
	}
	add_removed(res, parts[i], nb_removed, len);
	return (append_replace(res, len + nb_removed, replace));
}

void	write_completed_version(size_t *current, size_t *len, char *res)
{
	write_n_char(*current, '\b');
	write_n_char(*len, ' ');
	write_n_char(*len, '\b');
	ft_putstr(res);
}

char	autocomplete(char **line, size_t *current, size_t *len, char **env)
{
	t_linked_list	*candidates;
	char			**args;
	char			*res;
	int				nb_removed;

	candidates = new_list();
	args = split_command_in_args(*line);
	if (!args || strstrlen(args) == 0)
		return (0);
	if (strstrlen(args) == 1)
		look_for_matching_exec(args[0], candidates, env);
	else if (strstrlen(args) == 2 && ft_strcmp(args[0], "cd") == 0)
		look_for_matching_dir(args[1], candidates);
	else
		look_for_matching_file(args[strstrlen(args) - 1], candidates);
	res = match(get_end(args[strstrlen(args) - 1], &nb_removed), candidates);
	if (!res)
		return (0);
	res = replace_end(args, res, nb_removed);
	*line = res;
	write_completed_version(current, len, res);
	*len = ft_strlen(res);
	*current = *len;
	return (0);
}
