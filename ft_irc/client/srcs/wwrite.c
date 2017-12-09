/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wwrite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:53:52 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 16:53:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc_client.h"

char	green_instruction(char *str, int ind)
{
	if (str[ind] == '|' && str[ind + 1] == '>' && str[ind + 2] == ' ')
		return (1);
	return (0);
}

char	red_instruction(char *str, int ind)
{
	if (str[ind] == '|' && str[ind + 1] == 'x' && str[ind + 2] == ' ')
		return (1);
	return (0);
}

void	maybe_green_or_red_instruction(char *str, int *start, char *color)
{
	if (green_instruction(str, *start))
	{
		*color = 2;
		*start += 3;
	}
	else if (red_instruction(str, *start))
	{
		*color = 1;
		*start += 3;
	}
}

void	small_wwrite(t_window *window, char *str)
{
	wwrite_chars(window, str, ft_strlen(str), 0);
	wrefresh(window);
	wrefresh(g_windows.input_win);
}

void	wwrite(t_window *window, char *str)
{
	int		start;
	int		i;
	char	color;

	color = 0;
	if (ft_strlen(str) < 4)
		return (small_wwrite(window, str));
	start = 0;
	maybe_green_or_red_instruction(str, &start, &color);
	i = start;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			wwrite_chars(window, str + start, i - start + 1, color);
			color = 0;
			start = i + 1;
			maybe_green_or_red_instruction(str, &start, &color);
		}
		i++;
	}
	if (i - start > 1)
		wwrite_chars(window, str + start, i - start, color);
	wrefresh(window);
	wrefresh(g_windows.input_win);
}
