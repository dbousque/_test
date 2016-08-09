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

static void	print_ft_ntoa_base2(size_t n, char *base, int base_length,
															int res_length)
{
	char	res[res_length + 1];
	int		i;

	res[res_length] = '\0';
	i = res_length - 1;
	while (i >= 0)
	{
		res[i] = base[n % base_length];
		n /= base_length;
		i--;
	}
	write(1, res, ft_strlen(res));
}

void		print_ft_ntoa_base(size_t n, char *base)
{
	int		base_length;
	int		res_length;

	base_length = ft_strlen(base);
	if (base_length < 2)
		return ;
	res_length = ft_get_res_length(n, base_length);
	print_ft_ntoa_base2(n, base, base_length, res_length);
}