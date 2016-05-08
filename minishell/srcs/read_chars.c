/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:40:45 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:40:47 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	cursor_stuff_one(char tmp_char, char **line, size_t len_current_size[],
																	char **env)
{
	size_t		*len;
	size_t		*current;
	size_t		*size;

	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	size = &(len_current_size[2]);
	if (tmp_char == 1)
		place_cursor_start_of_line(current);
	else if (tmp_char == '\t')
	{
		if (autocomplete(line, current, len, env))
			*size = *len;
	}
	else if (tmp_char == 5)
	{
		ft_putstr(*line + *current);
		*current = *len;
	}
	else
		return (0);
	return (1);
}

void	navigate_history(char tmp_char, char **line, t_linked_list *history,
												size_t len_current_size[])
{
	int			*history_ind;
	size_t		*len;
	size_t		*current;
	size_t		*size;

	history_ind = (int*)&(len_current_size[3]);
	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	size = &(len_current_size[2]);
	if ((tmp_char == 3 && history->len > 1 && *history_ind > 1)
		|| (tmp_char == 4 && history->len > 1 && *history_ind < history->len))
	{
		write_n_char(*current, '\b');
		write_n_char(*len, ' ');
		write_n_char(*len, '\b');
		if ((tmp_char == 3 && history->len > 1 && *history_ind > 1))
			*line = get_last_history(history, *line, len, history_ind);
		else
			*line = get_next_history(history, len, history_ind);
		ft_putstr(*line);
		*size = *len;
		*current = *len;
	}
}

void	arrows_management(char **line, t_linked_list *history,
											size_t len_current_size[])
{
	char		tmp_char;
	size_t		*len;
	size_t		*current;

	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	tmp_char = arrow(27);
	if (tmp_char == 1 && *current > 0)
	{
		write(1, "\b", 1);
		(*current)--;
	}
	else if (tmp_char == 2 && *current < *len)
	{
		write(1, *line + *current, 1);
		(*current)++;
	}
	else
		navigate_history(tmp_char, line, history, len_current_size);
}

char	remove_char(char tmp_char, char **line, size_t *current, size_t *len)
{
	if (tmp_char == 127)
	{
		if (*current > 0)
		{
			remove_char_at_pos(*line, *current, *len);
			(*len)--;
			(*current)--;
		}
		return (1);
	}
	return (0);
}

void	read_chars(char **env, t_linked_list *history, char **line,
											size_t len_current_size[])
{
	char		tmp_char;
	size_t		*len;
	size_t		*current;
	size_t		*size;

	len = &(len_current_size[0]);
	current = &(len_current_size[1]);
	size = &(len_current_size[2]);
	while ((tmp_char = (char)getch()) != '\n')
	{
		if (!cursor_stuff_one(tmp_char, line, len_current_size, env)
			&& !remove_char(tmp_char, line, current, len))
		{
			if (tmp_char == 27)
				arrows_management(line, history, len_current_size);
			else
			{
				if (*len == *size)
					*line = double_size(*line, size);
				add_char_at_pos(*line, *current, *len, tmp_char);
				(*len)++;
				(*current)++;
			}
		}
	}
}
