/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_tetrimino2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:02:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/03 16:34:05 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				ft_is_semibarre(t_tetrimino *p)
{
	if (p->width == 2 && p->heigth == 3)
	{
		if (p->content[0][0] == '#' && p->content[1][0] == '#'
				&& p->content[2][0] == '#'
				&& (p->content[0][1] == '#' || p->content[2][1] == '#'))
			return (1);
		if (p->content[0][1] == '#' && p->content[1][1] == '#'
				&& p->content[2][1] == '#'
				&& (p->content[0][0] == '#' || p->content[2][0] == '#'))
			return (1);
	}
	if (p->heigth == 2 && p->width == 3)
	{
		if (p->content[0][0] == '#' && p->content[0][1] == '#'
				&& p->content[0][2] == '#'
				&& (p->content[1][0] == '#' || p->content[1][2] == '#'))
			return (1);
		if (p->content[1][0] == '#' && p->content[1][1] == '#'
				&& p->content[1][2] == '#'
				&& (p->content[0][0] == '#' || p->content[0][2] == '#'))
			return (1);
	}
	return (0);
}

int				ft_is_torti(t_tetrimino *p)
{
	if (p->width == 3 && p->heigth == 2)
	{
		if (p->content[0][0] == '#' && p->content[0][1] == '#'
				&& p->content[1][1] == '#' && p->content[1][2] == '#')
			return (1);
		if (p->content[1][0] == '#' && p->content[1][1] == '#'
				&& p->content[0][1] == '#' && p->content[0][2] == '#')
			return (1);
	}
	if (p->heigth == 3 && p->width == 2)
	{
		if (p->content[0][0] == '#' && p->content[1][0] == '#'
				&& p->content[1][1] == '#' && p->content[2][1] == '#')
			return (1);
		if (p->content[0][1] == '#' && p->content[1][1] == '#'
				&& p->content[1][0] == '#' && p->content[2][0] == '#')
			return (1);
	}
	return (0);
}

int				ft_valid_tetrimino(t_tetrimino *piece)
{
	if (!ft_has_four(piece))
		return (0);
	if (ft_is_carre(piece))
		return (1);
	if (ft_is_barre(piece))
		return (1);
	if (ft_is_fleche(piece))
		return (1);
	if (ft_is_semibarre(piece))
		return (1);
	if (ft_is_torti(piece))
		return (1);
	return (0);
}
