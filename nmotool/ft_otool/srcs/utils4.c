/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:37:26 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:40:12 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

uint32_t	handle_type(uint32_t typ, char option)
{
	static uint32_t		type = 0;

	if (option == 1)
		type = typ;
	return (type);
}

uint32_t	get_filetype(void)
{
	return (handle_type(0, 2));
}

void		set_filetype(uint32_t type)
{
	handle_type(type, 1);
}

void		ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
