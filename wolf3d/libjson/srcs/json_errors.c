/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:13:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 17:13:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjson.h"

void	*open_failed(void)
{
	ft_putendl_fd("Could not open file", 2);
	return (NULL);
}

void	*max_size_exceeded(char *filename, int max_size)
{
	ft_printf("Maximum file size of %d bytes ", max_size);
	ft_printf("exceeded while reading file \"%s\"\n", filename);
	return (NULL);
}

void	malloc_error(void)
{
	write(2, "Could not allocate enough memory.\n", 34);
	exit(1);
}

void	wrong_format(void)
{
	ft_putstr_fd("File format is invalid.\n", 2);
	exit(0);
}

void	no_colon(void)
{
	ft_putendl_fd("No colon found beetween key and value.", 2);
	exit(0);
}
