/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:53:54 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 17:54:11 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	set_current_options(void *ptr)
{
	get_set_options_handler(ptr, 1);
}

void	*get_current_options(void)
{
	return (get_set_options_handler(NULL, 2));
}
