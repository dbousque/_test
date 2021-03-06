/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 16:41:22 by dbousque          #+#    #+#             */
/*   Updated: 2016/08/15 12:35:03 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(str, 1);
}

void	print_malloc_call2(char option, void *ptr, size_t size)
{
	if (option == REALLOCF)
	{
		ft_putstr("-- REALLOCF CALLED WITH ");
		print_address(ptr);
		ft_putstr(" ");
		print_number(size);
		ft_putstr("\n");
	}
}

void	print_malloc_call(char option, void *ptr, size_t size)
{
	if (option == ALLOC)
	{
		ft_putstr("-- MALLOC CALLED WITH ");
		print_number(size);
		ft_putstr("\n");
	}
	else if (option == REALLOC)
	{
		ft_putstr("-- REALLOC CALLED WITH ");
		print_address(ptr);
		ft_putstr(" ");
		print_number(size);
		ft_putstr("\n");
	}
	else if (option == FREE)
	{
		ft_putstr("-- FREE CALLED WITH ");
		print_address(ptr);
		ft_putstr("\n");
	}
	print_malloc_call2(option, ptr, size);
}

void	print_malloc_return(char option, void *ptr)
{
	if (option == ALLOC)
	{
		ft_putstr("-- MALLOC RETURNS ");
		print_address(ptr);
		ft_putstr("\n");
	}
	else if (option == REALLOC)
	{
		ft_putstr("-- REALLOC RETURNS ");
		print_address(ptr);
		ft_putstr("\n");
	}
	else if (option == REALLOCF)
	{
		ft_putstr("-- REALLOCF RETURNS ");
		print_address(ptr);
		ft_putstr("\n");
	}
}
