/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 12:00:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/18 18:00:42 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_puthexa(unsigned long long value)
{
	char	*res;

	if ((res = ft_ntoa_base_un(value, "0123456789abcdef")))
	{
		ft_putstr(res);
		return (ft_strlen(res));
	}
	return (0);
}

int		ft_puthexa_maj(unsigned long long value)
{
	char	*res;

	if ((res = ft_ntoa_base_un(value, "0123456789ABCDEF")))
	{
		ft_putstr(res);
		return (ft_strlen(res));
	}
	return (0);
}
