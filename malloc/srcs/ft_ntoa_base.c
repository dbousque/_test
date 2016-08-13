/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ntoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 15:51:25 by dbousque          #+#    #+#             */
/*   Updated: 2016/07/25 16:43:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"



	#  include <stdio.h>

static int	ft_get_res_length(unsigned long long n, int base_length)
{
	int		i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= base_length;
		i++;
	}
	return (i);
}

void	print_ft_ntoa_base_fd2(size_t n, char *base, int res_length, int fd)
{
	char	res[res_length + 1];
	int		i;
	int		base_length;

	base_length = ft_strlen(base);
	res[res_length] = '\0';
	i = res_length - 1;
	while (i >= 0)
	{
		res[i] = base[n % base_length];
		n /= base_length;
		i--;
	}
	write(fd, res, ft_strlen(res));
}

void	print_ft_ntoa_base_fd(size_t n, char *base, int fd)
{
	int		base_length;
	int		res_length;

	base_length = ft_strlen(base);
	if (base_length < 2)
		return ;
	res_length = ft_get_res_length(n, base_length);
	print_ft_ntoa_base_fd2(n, base, res_length, fd);
}

void		print_ft_ntoa_base(size_t n, char *base)
{
	print_ft_ntoa_base_fd(n, base, 1);
}
