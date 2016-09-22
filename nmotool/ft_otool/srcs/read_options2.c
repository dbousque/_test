/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:38:47 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:39:03 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	set_current_options(void *ptr)
{
	get_set_options_handler(ptr, 1);
}

void	*get_current_options(void)
{
	return (get_set_options_handler(NULL, 2));
}
