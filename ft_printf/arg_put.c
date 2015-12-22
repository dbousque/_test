/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 18:58:28 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/22 19:03:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		arg_putnbr(va_list ap, char flag, char **str)
{
	long long	res;
	int			length;

	if (flag == L)
		res = va_arg(ap, long);
	else if (flag == LL)
		res = va_arg(ap, long long);
	else if (flag == H)
		res = (short)va_arg(ap, int);
	else if (flag == HH)
		res = (char)va_arg(ap, int);
	else if (flag == J)
		res = va_arg(ap, intmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, int);
	length = ft_putlonglong(res, str);
	return (length);
}

int		arg_putnbr_long(va_list ap, char flag, char **str)
{
	long long	res;
	int			length;

	if (flag == L || flag == LL)
		res = va_arg(ap, long long);
	else
		res = va_arg(ap, long);
	length = ft_putlonglong(res, str);
	return (length);
}

int		arg_putnbr_un(va_list ap, char flag, char **str)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_putlonglong_un(res, str);
	return (length);
}

int		arg_putnbr_un_long(va_list ap, char flag, char **str)
{
	unsigned long long	res;
	int					length;

	if (flag == L || flag == LL)
		res = va_arg(ap, unsigned long long);
	else
		res = va_arg(ap, unsigned long);
	length = ft_putlonglong_un(res, str);
	return (length);
}

int		arg_putchar(va_list ap, char flag, char **str)
{
	char	res;
	wchar_t	res2;
	int		length;

	length = 1;
	if (flag == L)
	{
		res2 = va_arg(ap, wchar_t);
		length = ft_put_wchar(res2, str);
	}
	else
	{
		res = va_arg(ap, int);
		*str = (char*)malloc(sizeof(char) * 2);
		(*str)[0] = (unsigned char)res;
		(*str)[1] = '\0';
	}
	return (length);
}

int		arg_putwchar(va_list ap, char flag, char **str)
{
	wchar_t	res;

	(void)flag;
	res = va_arg(ap, wchar_t);
	return (ft_put_wchar(res, str));
}

int		arg_putunicode(va_list ap, char flag, char **str)
{
	wchar_t	*res;
	int		length;
(void)flag;
	res = va_arg(ap, wchar_t*);
	if (res)
		length = ft_putunicode(res, str);
	else
	{
		*str = "(null)";
		return (6);
	}
	return (length);
}

int		arg_putstr(va_list ap, char flag, char **str)
{
	char	*res;

	if (flag == L)
		return (arg_putunicode(ap, flag, str));
	res = va_arg(ap, char*);
	if (res)
		*str = res;
	else
	{
		*str = "(null)";
		return (6);
	}
	return (ft_strlen(*str));
}

int		arg_putaddr(va_list ap, char flag, char **str)
{
	void	*res;
	int		length;

	(void)flag;
	res = va_arg(ap, void*);
	length = ft_putaddr(res, 1, str);
	return (length);
}

int		arg_putoctal(va_list ap, char flag, char **str)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_putoctal_un(res, str);
	return (length);
}

int		arg_putoctal_long(va_list ap, char flag, char **str)
{
	unsigned long long	res;
	int					length;

	if (flag == L || flag == LL)
		res = va_arg(ap, unsigned long long);
	else
		res = va_arg(ap, unsigned long);
	length = ft_putoctal_un(res, str);
	return (length);
}

int		arg_puthexa(va_list ap, char flag, char **str)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_puthexa(res, str);
	return (length);
}

int		arg_puthexa_maj(va_list ap, char flag, char **str)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, uintmax_t);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	length = ft_puthexa_maj(res, str);
	return (length);
}
