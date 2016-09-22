/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:59:35 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:21:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

char	*handle_stringtable(char *ptr, char option)
{
	static char		*str = NULL;

	if (option == 1)
		str = ptr;
	return (str);
}
