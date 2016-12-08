/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_client4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:31:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:33:01 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_client.h"

char	return_get_error(char *error)
{
	ft_putstr(error);
	return (0);
}

char	return_error(char *error)
{
	ft_putstr(error);
	return (0);
}
