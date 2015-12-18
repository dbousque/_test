/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 13:39:26 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/18 18:02:23 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putlong(long value)
{
	char	*res;

	if ((res = ft_ntoa_base(value, "0123456789")))
	{
		ft_putstr(res);
		return (ft_strlen(res));
	}
	return (0);
}

int		ft_putlong_un(unsigned long value)
{
	char	*res;

	if ((res = ft_ntoa_base_un(value, "0123456789")))
	{
		ft_putstr(res);
		return (ft_strlen(res));
	}
	return (0);
}
