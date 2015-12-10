/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_points.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:11:35 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/03 17:04:05 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_point		*ft_new_point(int x, int y)
{
	t_point		*res;

	if (!(res = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	res->x = x;
	res->y = y;
	return (res);
}

int			ft_closer(t_tetrimino *t, int x, int m, int closer)
{
	if (x + t->width < m || (closer && x + t->width <= m))
		return (1);
	return (0);
}

int			ft_clo2(t_tetrimino *t, int y, int m, int closer)
{
	if (y + t->heigth < m || (closer && y + t->heigth <= m))
		return (1);
	return (0);
}

t_list		*ft_ok_pnts(t_node2 *n, t_tetrimino *t, int m, t_node2 *be)
{
	t_list		*lst;
	t_list		*lstend;
	int			x;
	int			y;
	int			closer;

	lst = NULL;
	lstend = NULL;
	y = 0;
	closer = ft_could_be_closer(n, be, m);
	while (n->board[y] && (m == -1 || ft_clo2(t, y, m, closer)))
	{
		x = 0;
		while (n->board[y][x] && (m == -1 || ft_closer(t, x, m, closer)))
		{
			if (ft_can_put(n->board, x, y, t))
				ft_lstaddend(&lstend, ft_lstnew(ft_new_point(x, y),
					sizeof(t_point)));
			if (!lst)
				lst = lstend;
			x++;
		}
		y++;
	}
	return (lst);
}

int			ft_points_length(t_list *points)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = points;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
