/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dels.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:04:29 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/03 16:34:38 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_delstrstr(char **content)
{
	int		i;

	i = 0;
	while (content[i])
	{
		ft_strdel(&content[i]);
		i++;
	}
	free(content);
	content = NULL;
}

void	ft_delstrstr2(char **strstr)
{
	int		i;

	i = 0;
	while (strstr[i])
	{
		free(strstr[i]);
		strstr[i] = NULL;
		i++;
	}
	free(strstr);
	strstr = NULL;
}

void	ft_del_tetris(t_tetrimino **tetris)
{
	int		i;

	i = 0;
	while (tetris[i])
	{
		ft_delstrstr(tetris[i]->content);
		free(tetris[i]);
		tetris[i] = NULL;
		i++;
	}
	free(tetris);
	tetris = NULL;
}

void	ft_del_points(void *point, size_t size)
{
	(void)size;
	free(point);
	point = NULL;
}

void	ft_free_node(t_node2 *node)
{
	if (node)
	{
		if (node->board)
		{
			ft_delstrstr(node->board);
			node->board = NULL;
		}
		free(node);
		node = NULL;
	}
}
