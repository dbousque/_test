/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:51:57 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/15 14:22:15 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	return (handle_malloc_option(size, ALLOC, NULL));
}

void	free(void *ptr)
{
	handle_malloc_option(0, FREE, ptr);
}

void	*realloc(void *ptr, size_t size)
{
	return (handle_malloc_option(size, REALLOC, ptr));
}

/*
** #   include <sys/resource.h>
** #   include <execinfo.h>
** void	*calloc(size_t count, size_t size)
** {
** 	static int n = 0;
** 	struct   rlimit limit;
** 	struct rusage r_usage;
** 	 getrlimit (RLIMIT_STACK, &limit);
**
** 	 n++;
** 	ft_putstr("STACK LIMIT (soft) : ");
** 	print_number(limit.rlim_cur);
** 	ft_putstr("\n");
** 	ft_putstr("STACK LIMIT (hard) : ");
** 	print_number(limit.rlim_max);
** 	ft_putstr("\n");
** 	getrusage(RUSAGE_SELF, &r_usage);
** 	ft_putstr("CURRENT STACK USE : ");
** 	print_number(r_usage.ru_maxrss);
** 	ft_putstr("\n");
**
** 	if (n == 50)
** 	{
** 		void* callstack[128];
** 	    int i;
** 	    int frames;
** 	    char** strs;
**
** 	    frames = backtrace(callstack, 128);
** 	    strs = backtrace_symbols(callstack, frames);
** 	    i = 0;
** 	    while (i < frames)
** 	    {
** 	        ft_putstr(strs[i]);
** 	        ft_putstr("\n");
** 	        i++;
** 	    }
** 	}
** 	ft_putstr("AFTER WHILE\n");
** 	return (handle_malloc_option(count * size, CALLOC, NULL));
** }
*/

void	*reallocf(void *ptr, size_t size)
{
	return (handle_malloc_option(size, REALLOCF, ptr));
}
