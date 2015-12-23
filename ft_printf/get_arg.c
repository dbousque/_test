/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 19:06:46 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/22 19:07:09 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_arg(char **str, va_list ap, t_format *format_var)
{
	int		length;

	length = 0;
	if (format_var->specifier == 'd' || format_var->specifier== 'i')
		length = arg_putnbr(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'c')
		length = arg_putchar(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 's')
		length = arg_putstr(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'u')
		length = arg_putnbr_un(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'p')
		length = arg_putaddr(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'o')
		length = arg_putoctal(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'x')
		length = arg_puthexa(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'X')
		length = arg_puthexa_maj(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'S')
		length = arg_putunicode(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'D')
		length = arg_putnbr_long(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'O')
		length = arg_putoctal_long(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'U')
		length = arg_putnbr_un_long(ap, format_var->length, str, format_var);
	else if (format_var->specifier == 'C')
		length = arg_putwchar(ap, format_var->length, str, format_var);
	return (length);
}
