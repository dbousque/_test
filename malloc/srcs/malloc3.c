/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 13:21:49 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/15 13:21:53 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem(void)
{
	handle_malloc_option(0, PRINT_MEM, NULL);
}

void	malloc_dump(void)
{
	handle_malloc_option(0, DUMP_HEXA, NULL);
}

void	malloc_help(void)
{
	handle_malloc_option(0, HELP, NULL);
}

void	malloc_help2(void)
{
	ft_putstr("  -- MALLOC --\n");
	ft_putstr("Implementation of malloc, free, realloc and reallocf.\n");
	ft_putstr("\nHelpers functions :\n  - show_alloc_mem()\n  - malloc_dump()");
	ft_putstr("\n  - malloc_free_zones()\n");
	ft_putstr("\nEnvironment variables :\n  - MALLOC_PRINT_DEBUG\n");
	ft_putstr("  - MALLOC_ALLOC_DEBUG\n  - MALLOC_ALWAYS_SHOW_ALLOC\n");
	ft_putstr("  - MALLOC_PRINT_CALLS\n  - MALLOC_ALWAYS_SHOW_FREE\n");
	ft_putstr("\nSpecial features :\n");
	ft_putstr("  - Thread-safe thanks to pthread mutexes\n  - ");
	ft_putstr("\nConcatenation of touching free blocks (defragmentation)\n");
}
