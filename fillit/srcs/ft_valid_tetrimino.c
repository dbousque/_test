/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_tetrimino.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:00:50 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/03 16:33:56 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				ft_has_four(t_tetrimino *piece)
{
	int		nb;
	int		i;
	int		x;

	i = 0;
	nb = 0;
	while (piece->content[i])
	{
		x = 0;
		while (piece->content[i][x])
		{
			if (piece->content[i][x] == '#')
				nb++;
			x++;
		}
		i++;
	}
	if (nb != 4)
		return (0);
	return (1);
}

int				ft_is_barre(t_tetrimino *p)
{
	if ((p->width == 1 && p->heigth == 4) || (p->width == 4 && p->heigth == 1))
		return (1);
	return (0);
}

int				ft_is_carre(t_tetrimino *piece)
{
	if (piece->width == 2 && piece->heigth == 2)
		return (1);
	return (0);
}

int				ft_is_fleche(t_tetrimino *p)
{
	if (p->width == 2 && p->heigth == 3)
	{
		if (p->content[0][0] == '#' && p->content[1][0] == '#'
				&& p->content[2][0] == '#' && p->content[1][1] == '#')
			return (1);
		if (p->content[0][1] == '#' && p->content[1][1] == '#'
				&& p->content[2][1] == '#' && p->content[1][0] == '#')
			return (1);
	}
	if (p->heigth == 2 && p->width == 3)
	{
		if (p->content[0][0] == '#' && p->content[0][1] == '#'
				&& p->content[0][2] == '#' && p->content[1][1] == '#')
			return (1);
		if (p->content[1][0] == '#' && p->content[1][1] == '#'
				&& p->content[1][2] == '#' && p->content[0][1] == '#')
			return (1);
	}
	return (0);
}
