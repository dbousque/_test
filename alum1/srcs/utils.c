/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/20 16:55:04 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 16:56:02 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

void	ft_putintint(int *board)
{
	int		i;

	i = 0;
	while (board[i])
	{
		ft_putnbr(board[i]);
		ft_putchar('\n');
		i++;
	}
}

int		ft_intlen(int *board)
{
	int		i;

	i = 0;
	while (board[i])
		i++;
	return (i);
}
