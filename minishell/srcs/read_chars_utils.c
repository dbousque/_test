/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_chars_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:40:52 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:40:54 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_char_at_pos(char *line, size_t current, size_t len)
{
	size_t	i;

	i = current;
	while (i < len)
	{
		line[i - 1] = line[i];
		i++;
	}
	line[i - 1] = '\0';
	clear_line((int)(len - current));
	write(1, "\b \b", 3);
	ft_putstr(line + current - 1);
	i = current;
	while (i < len)
	{
		write(1, "\b", 1);
		i++;
	}
}

char	arrow(char tmp_char)
{
	if (tmp_char == 27)
	{
		tmp_char = (char)getch();
		if (tmp_char == 91)
		{
			tmp_char = (char)getch();
			if (tmp_char == 68)
				return (1);
			if (tmp_char == 67)
				return (2);
			if (tmp_char == 65)
				return (3);
			if (tmp_char == 66)
				return (4);
		}
	}
	return (0);
}

void	place_cursor_start_of_line(size_t *current)
{
	while (*current > 0)
	{
		write(1, "\b", 1);
		(*current)--;
	}
}

char	*get_last_history(t_linked_list *history, char *line, size_t *len,
															int *history_ind)
{
	if (*history_ind == history->len)
	{
		free(history->elts[history->len - 1]);
		history->elts[history->len - 1] = ft_strdup(line);
	}
	(*history_ind)--;
	*len = ft_strlen(history->elts[*history_ind - 1]);
	return (ft_strdup(history->elts[*history_ind - 1]));
}

char	*get_next_history(t_linked_list *history, size_t *len, int *history_ind)
{
	(*history_ind)++;
	*len = ft_strlen(history->elts[*history_ind - 1]);
	return (ft_strdup(history->elts[*history_ind - 1]));
}
