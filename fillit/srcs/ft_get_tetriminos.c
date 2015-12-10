/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_tetriminos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:07:30 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/03 16:32:09 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			ft_get_min_max(int *min, int *max, char *content)
{
	int		i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '#' && i % 5 < *min)
			*min = i % 5;
		if (content[i] == '#' && i % 5 > *max)
			*max = i % 5;
		i++;
	}
}

void			ft_get_min_max2(int *min, int *max, char *content)
{
	int		i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '#' && i / 5 < *min)
			*min = i / 5;
		if (content[i] == '#' && i / 5 > *max)
			*max = i / 5;
		i++;
	}
}

t_tetrimino		*ft_new_tetrimino(char *content, int ind)
{
	t_tetrimino		*res;
	int				max;
	int				min;
	int				tmp[2];

	min = 10;
	max = -10;
	if (!(res = (t_tetrimino*)malloc(sizeof(t_tetrimino) * 1)))
		return (NULL);
	ft_get_min_max(&min, &max, content);
	if (max - min < 0)
		return (NULL);
	res->width = max - min + 1;
	tmp[0] = min;
	tmp[1] = max;
	min = 10;
	max = -10;
	ft_get_min_max2(&min, &max, content);
	res->heigth = max - min + 1;
	res->content = ft_strrip(content, tmp, min, max);
	res->letter = ind + 'A';
	ft_strdel(&content);
	return (res);
}

t_tetrimino		**ft_get_tetriminos(char *file_content)
{
	t_tetrimino		**tetris;
	t_tetrimino		*piece;
	int				i;
	int				ind;

	i = ft_strlen(file_content) / 21 + 1;
	if (!(tetris = (t_tetrimino**)malloc(sizeof(t_tetrimino*) * (i + 1))))
		return (NULL);
	tetris[i] = NULL;
	i = 0;
	ind = 0;
	while (i == 0 || file_content[i - 1])
	{
		if (ind >= 26)
			return (NULL);
		piece = ft_new_tetrimino(ft_strsub(file_content, i, 20), ind);
		if (!piece)
			return (NULL);
		if (!ft_valid_tetrimino(piece))
			return (NULL);
		tetris[ind] = piece;
		i += 21;
		ind++;
	}
	return (tetris);
}
