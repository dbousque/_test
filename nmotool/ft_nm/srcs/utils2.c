/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 18:01:13 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:01:15 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	bad_executable(void)
{
	print_error("Unrecognized file format");
}

void	*bad_executable_null(void)
{
	bad_executable();
	return (NULL);
}

char	valid_pointer(void *ptr)
{
	static void		*start = NULL;
	static void		*end = NULL;

	if (!ptr)
	{
		start = NULL;
		end = NULL;
	}
	else if (!start)
		start = ptr;
	else if (!end)
		end = ptr;
	else
	{
		if (ptr < start || ptr >= end)
		{
			bad_executable();
			return (0);
		}
	}
	return (1);
}

void	set_valid_pointer(void *start, void *end)
{
	reset_valid_pointer();
	valid_pointer(start);
	valid_pointer(end);
}

void	reset_valid_pointer(void)
{
	valid_pointer(NULL);
}
