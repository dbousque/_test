/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:16:45 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/06 13:00:09 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	ft_fill_at(char **board, int i_y, int i_x)
{
	if (!board[i_y] || !board[i_y][i_x])
		return ('.');
	return (board[i_y][i_x]);
}

char	**ft_strip_strstr(char **board, int x, t_tetrimino **t)
{
	int		i_x;
	int		i_y;
	char	**res;

	x = (x < t[0]->heigth ? t[0]->heigth : x);
	x = (x < t[0]->width ? t[0]->width : x);
	if (!(res = (char**)malloc(sizeof(char*) * (x + 1))))
		return (NULL);
	res[x] = NULL;
	i_y = 0;
	while (i_y < x)
	{
		i_x = 0;
		if (!(res[i_y] = (char*)malloc(sizeof(char) * (x + 1))))
			return (NULL);
		res[i_y][x] = '\0';
		while (i_x < x)
		{
			res[i_y][i_x] = ft_fill_at(board, i_y, i_x);
			i_x++;
		}
		i_y++;
	}
	return (res);
}

char	**ft_rip_res(char **board, t_tetrimino **tetris)
{
	int		x;
	int		y;
	int		i_x;
	int		i_y;

	x = 0;
	while (board[x] && ft_char_in_line(board[x]))
		x++;
	i_y = 0;
	y = 0;
	while (i_y < x)
	{
		i_x = 0;
		while (board[i_y][i_x])
		{
			if (board[i_y][i_x] != '.' && i_x + 1 > y)
				y = i_x + 1;
			i_x++;
		}
		i_y++;
	}
	if (x > y)
		return (ft_strip_strstr(board, x, tetris));
	return (ft_strip_strstr(board, y, tetris));
}

char	**ft_strrip(char *content, int x[], int y_min, int y_max)
{
	char	**res;
	int		i;
	int		y;

	if (!(res = (char**)malloc(sizeof(char*) * (y_max - y_min + 2))))
		return (NULL);
	res[y_max - y_min + 1] = NULL;
	i = 0;
	while (i < y_max - y_min + 1)
	{
		if (!(res[i] = (char*)malloc(sizeof(char) * (x[1] - x[0] + 2))))
			return (NULL);
		y = 0;
		res[i][x[1] - x[0] + 1] = '\0';
		while (y < x[1] - x[0] + 1)
		{
			res[i][y] = content[x[0] + y + ((y_min + i) * 5)];
			y++;
		}
		i++;
	}
	return (res);
}

char	**ft_allocate_strstr(int x, int y, char c)
{
	int		i;
	int		a;
	char	**board;

	i = 0;
	if (!(board = (char**)malloc(sizeof(char*) * (y + 1))))
		return (NULL);
	board[y] = NULL;
	while (i < y)
	{
		if (!(board[i] = (char*)malloc(sizeof(char) * (x + 1))))
			return (NULL);
		board[i][x] = '\0';
		a = 0;
		while (a < x)
		{
			board[i][a] = c;
			a++;
		}
		i++;
	}
	return (board);
}
