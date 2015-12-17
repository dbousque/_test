/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 14:52:44 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/17 14:52:50 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_unexpected_error(void)
{
	ft_putendl("unexpected error");
	return (1);
}

int		ft_map_error(void)
{
	ft_putendl("map error");
	return (1);
}

int		ft_connection_failed(void)
{
	ft_putendl("connection to X server failed");
	return (1);
}
