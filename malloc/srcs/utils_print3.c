/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 12:24:41 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/15 12:25:01 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_debug_bad_free(void *ptr)
{
	char	*tmp;

	tmp = "Free called on unallocated pointer : ";
	write(1, tmp, ft_strlen(tmp));
	print_address(ptr);
	write(1, "\n", 1);
}
