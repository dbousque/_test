/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:39:58 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:40:01 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_char_at_pos(char *line, size_t current, size_t len, char c)
{
	size_t	i;

	i = len;
	while (i > current)
	{
		line[i] = line[i - 1];
		i--;
	}
	line[current] = c;
	line[len + 1] = '\0';
	ft_putstr(line + current);
	i = current;
	while (i < len)
	{
		write(1, "\b", 1);
		i++;
	}
}

void	clear_line(int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		write(1, " ", 1);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		write(1, "\b", 1);
		i++;
	}
}

void	write_n_char(size_t n, char c)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

char	*get_dir_name(char *start)
{
	int		i;
	char	*res;
	int		x;

	i = ft_strlen(start);
	i--;
	while (i >= 0 && start[i] != '/')
		i--;
	if (!(res = (char*)malloc(sizeof(char) * (i + 2))))
		malloc_error();
	res[i + 1] = '\0';
	x = 0;
	while (x <= i)
	{
		res[x] = start[x];
		x++;
	}
	return (res);
}

char	*get_input(char **env, t_linked_list *history)
{
	char	*line;
	size_t	len_current_size[4];

	if (!(line = (char*)malloc(sizeof(char) * 6)))
		malloc_error();
	line[0] = '\0';
	len_current_size[0] = 0;
	len_current_size[1] = 0;
	len_current_size[2] = 5;
	len_current_size[3] = history->len;
	read_chars(env, history, &line, len_current_size);
	if (len_current_size[0] == len_current_size[2])
		line = double_size(line, &(len_current_size[2]));
	line[len_current_size[0]] = '\0';
	free(history->elts[history->len - 1]);
	if (history->len == 1
		|| ft_strcmp(history->elts[history->len - 2], line) != 0)
		history->elts[history->len - 1] = ft_strdup(line);
	else
		history->len--;
	write(1, "\n", 1);
	return (line);
}
