/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 15:59:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/19 16:42:26 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



#include <stdio.h>

int				pow2(int nb)
{
	int		res;

	res = 1;
	while (nb > 0)
	{
		res *= 2;
		nb--;
	}
	return (res);
}

unsigned char	byte_array_to_uchar(char *byte)
{
	unsigned char	res;
	int				i;

	i = 7;
	res = 0;
	while (i >= 0)
	{
		res += (byte[i] - '0') * pow2(7 - i);
		i--;
	}
	return (res);
}

void	assign_bit(unsigned char *byte, int nb, char val)
{
	byte[nb] = val;
}

void	write_res_to_tmp(char *res, char *tmp, int tmp_length)
{
	int		res_length;
	int		i;

	res_length = ft_strlen(res);
	i = 0;
	while (i < tmp_length - res_length)
	{
		tmp[i] = '0';
		i++;
	}
	while (i < tmp_length)
	{
		tmp[i] = res[i - (tmp_length - res_length)];
		i++;
	}
}

void	cpy_n_bits(char *res, char *tmp, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		res[i] = tmp[i];
		i++;
	}
}

void	ft_put_one_uni(wchar_t car)
{
	write(1, (unsigned char*)&car, 1);
}

void	ft_put_two_uni(wchar_t car)
{
	char	*val[2];
	char	tmp[12];
	unsigned char	tmp_value;
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 11);
	tmp[11] = '\0';
	val[0] = (char*)malloc(sizeof(char) * 8);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '0';
	cpy_n_bits(val[0] + 3, tmp, 5);
	
	val[1] = (char*)malloc(sizeof(char) * 8);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 5, 6);
	
	tmp_value = byte_array_to_uchar(val[0]);
	write(1, &tmp_value, 1);
	tmp_value = byte_array_to_uchar(val[1]);
	write(1, &tmp_value, 1);
}

void	ft_putendl_sp(char *str)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_put_three_uni(wchar_t car)
{
	char	*val[3];
	char	tmp[17];
	unsigned char	tmp_value;
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 16);
	tmp[16] = '\0';
	val[0] = (char*)malloc(sizeof(char) * 8);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '1';
	val[0][3] = '0';
	cpy_n_bits(val[0] + 4, tmp, 4);

	val[1] = (char*)malloc(sizeof(char) * 8);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 4, 6);
	
	val[2] = (char*)malloc(sizeof(char) * 8);
	val[2][0] = '1';
	val[2][1] = '0';
	cpy_n_bits(val[2] + 2, tmp + 10, 6);

	tmp_value = byte_array_to_uchar(val[0]);
	write(1, &tmp_value, 1);
	tmp_value = byte_array_to_uchar(val[1]);
	write(1, &tmp_value, 1);
	tmp_value = byte_array_to_uchar(val[2]);
	write(1, &tmp_value, 1);
}

void	ft_put_four_uni(wchar_t car)
{
	char	*val[4];
	char	tmp[22];
	unsigned char	tmp_value;
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 21);
	tmp[21] = '\0';
	val[0] = (char*)malloc(sizeof(char) * 8);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '1';
	val[0][3] = '1';
	val[0][4] = '0';
	cpy_n_bits(val[0] + 5, tmp, 3);

	val[1] = (char*)malloc(sizeof(char) * 8);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 3, 6);
	
	val[2] = (char*)malloc(sizeof(char) * 8);
	val[2][0] = '1';
	val[2][1] = '0';
	cpy_n_bits(val[2] + 2, tmp + 9, 6);

	val[3] = (char*)malloc(sizeof(char) * 8);
	val[3][0] = '1';
	val[3][1] = '0';
	cpy_n_bits(val[3] + 2, tmp + 15, 6);

	tmp_value = byte_array_to_uchar(val[0]);
	write(1, &tmp_value, 1);
	tmp_value = byte_array_to_uchar(val[1]);
	write(1, &tmp_value, 1);
	tmp_value = byte_array_to_uchar(val[2]);
	write(1, &tmp_value, 1);
	tmp_value = byte_array_to_uchar(val[3]);
	write(1, &tmp_value, 1);
}

int		ft_put_wchar(wchar_t car)
{
	int		length;

	length = 0;
	if (car < 0x0000007F)
	{
		length = 1;
		ft_put_one_uni(car);
	}
	else if (car < 0x000007FF)
	{
		length = 2;
		ft_put_two_uni(car);
	}
	else if (car < 0x0000FFFF)
	{
		length = 3;
		ft_put_three_uni(car);
	}
	else if (car < 0x001FFFFF)
	{
		length = 4;
		ft_put_four_uni(car);
	}
	return (length);
}

int		ft_putunicode(wchar_t *uni)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (uni[i])
	{
		length += ft_put_wchar(uni[i]);
		i++;
	}
	return (length);
}
