/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 15:59:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/19 16:42:26 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_unicodelen(wchar_t *uni)
{
	(void)uni;
	return (0);
}

void	ft_putunicode(wchar_t *uni)
{
	int		i;

	i = 0;
	//ft_putchar('\n');
	while (uni[i])
	{
		//ft_putnbr(uni[i]);
		//ft_putchar('\n');
		write(1, (void*)&uni[i], 1);
		i++;
	}
}
