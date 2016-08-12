/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:52:33 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 15:59:33 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_number_fd(size_t number, int fd)
{
	char	numbers[100];
	int		ind;

	if (number == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	ind = 99;
	while (number > 0)
	{
		numbers[ind] = (number % 10) + '0';
		number /= 10;
		ind--;
	}
	ind++;
	while (ind < 100)
	{
		write(fd, numbers + ind, 1);
		ind++;
	}
}

void	print_number(size_t number)
{
	print_number_fd(number, 1);
}

void	print_address_fd(void *ptr, int fd)
{
	write(fd, "0x", 2);
	print_ft_ntoa_base_fd((size_t)ptr, "0123456789ABCDEF", fd);
}

void	print_address(void *ptr)
{
	print_address_fd(ptr, 1);
}

void	print_byte(void *ptr)
{
	print_ft_ntoa_base(*((char*)ptr), "0123456789abcdef");
}
