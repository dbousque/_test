/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 15:59:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/21 16:00:39 by dbousque         ###   ########.fr       */
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

int		ft_put_one_uni(wchar_t car, char *str)
{
	if (!((char*)malloc(sizeof(char) * 2)))
		return (0);
	str[0] = (unsigned char)car;
	str[1] = '\0';
	return (1);
}

int		ft_put_two_uni(wchar_t car, char *str)
{
	char	*val[2];
	char	tmp[12];
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 11);
	free(res);
	res = NULL;
	tmp[11] = '\0';
	if (!(val[0] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '0';
	cpy_n_bits(val[0] + 3, tmp, 5);
	
	if (!(val[1] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 5, 6);
	
	str[0] = byte_array_to_uchar(val[0]);
	str[1] = byte_array_to_uchar(val[1]);
	free(val[0]);
	free(val[1]);
	val[0] = NULL;
	val[1] = NULL;
	return (2);
}

int		ft_put_three_uni(wchar_t car, char *str)
{
	char	*val[3];
	char	tmp[17];
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 16);
	tmp[16] = '\0';
	if (!(val[0] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '1';
	val[0][3] = '0';
	cpy_n_bits(val[0] + 4, tmp, 4);

	if (!(val[1] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 4, 6);
	
	if (!(val[2] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[2][0] = '1';
	val[2][1] = '0';
	cpy_n_bits(val[2] + 2, tmp + 10, 6);

	str[0] = byte_array_to_uchar(val[0]);
	str[1] = byte_array_to_uchar(val[1]);
	str[2] = byte_array_to_uchar(val[2]);

	free(val[0]);
	free(val[1]);
	free(val[2]);
	val[0] = NULL;
	val[1] = NULL;
	val[2] = NULL;
	return (3);
}

int		ft_put_four_uni(wchar_t car, char *str)
{
	char	*val[4];
	char	tmp[22];
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 21);
	tmp[21] = '\0';
	if (!(val[0] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '1';
	val[0][3] = '1';
	val[0][4] = '0';
	cpy_n_bits(val[0] + 5, tmp, 3);

	if (!(val[1] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 3, 6);
	
	if (!(val[2] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[2][0] = '1';
	val[2][1] = '0';
	cpy_n_bits(val[2] + 2, tmp + 9, 6);

	if (!(val[3] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[3][0] = '1';
	val[3][1] = '0';
	cpy_n_bits(val[3] + 2, tmp + 15, 6);

	str[0] = byte_array_to_uchar(val[0]);
	str[1] = byte_array_to_uchar(val[1]);
	str[2] = byte_array_to_uchar(val[2]);
	str[3] = byte_array_to_uchar(val[3]);

	free(val[0]);
	free(val[1]);
	free(val[2]);
	free(val[3]);
	val[0] = NULL;
	val[1] = NULL;
	val[2] = NULL;
	val[3] = NULL;
	return (4);
}

int		ft_put_wchar(wchar_t car, char **str)
{
	if (car < 0x0000007F)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 2)))
			return (0);
		(*str)[1] = '\0';
		return (ft_put_one_uni(car, *str));
	}
	if (car < 0x000007FF)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 3)))
			return (0);
		(*str)[2] = '\0';
		return (ft_put_two_uni(car, *str));
	}
	if (car < 0x0000FFFF)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 4)))
			return (0);
		(*str)[3] = '\0';
		return (ft_put_three_uni(car, *str));
	}
	if (car < 0x001FFFFF)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 5)))
			return (0);
		(*str)[4] = '\0';
		return (ft_put_four_uni(car, *str));
	}
	return (0);
}

void	del_maillon(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel((char**)&content);
	content = NULL;
}

char	*lst_to_str(t_list *strs)
{
	t_list	*tmp;
	int		length;
	char	*res;

	tmp = strs;
	length = 0;
	while (tmp)
	{
		length += tmp->content_size - 1;
		tmp = tmp->next;
	}
	if (!(res = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	res[length] = '\0';
	length = 0;
	while (strs)
	{
		ft_strcpy(res + length, strs->content);
		length += strs->content_size - 1;
		strs = strs->next;
	}
	ft_lstdel(&strs, del_maillon);
	return (res);
}

int		empty_str(char **str)
{
	if ((*str = (char*)malloc(sizeof(char))))
		(*str)[0] = '\0';
	else
		*str = NULL;
	return (0);
}

int		ft_putunicode(wchar_t *uni, char **str)
{
	int		i;
	int		length;
	char	*tmp;
	t_list	*strs;
	t_list	*strs_end;

	strs = NULL;
	strs_end = NULL;
	i = 0;
	length = 0;
	tmp = NULL;
	while (uni[i])
	{
		length += ft_put_wchar(uni[i], &tmp);
		if (!tmp)
			return (empty_str(str));
		ft_putendl("LOL2");
		ft_lstaddend(&strs_end, ft_lstnew(tmp, ft_strlen(tmp) + 1));
		ft_putendl("LOL3");
		free(tmp);
		if (!strs)
			strs = strs_end;
		i++;
	}
	*str = lst_to_str(strs);
	return (length);
}
