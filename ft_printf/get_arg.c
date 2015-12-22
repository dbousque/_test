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

int		get_arg(char **str, va_list ap, char flag, char c)
{
	int		length;

	length = 0;
	if (c == 'd' || c == 'i')
		length = arg_putnbr(ap, flag, str);
	else if (c == 'c')
		length = arg_putchar(ap, flag, str);
	else if (c == 's')
		length = arg_putstr(ap, flag, str);
	else if (c == 'u')
		length = arg_putnbr_un(ap, flag, str);
	else if (c == 'p')
		length = arg_putaddr(ap, flag, str);
	else if (c == 'o')
		length = arg_putoctal(ap, flag, str);
	else if (c == 'x')
		length = arg_puthexa(ap, flag, str);
	else if (c == 'X')
		length = arg_puthexa_maj(ap, flag, str);
	else if (c == 'S')
		length = arg_putunicode(ap, flag, str);
	else if (c == 'D')
		length = arg_putnbr_long(ap, flag, str);
	else if (c == 'O')
		length = arg_putoctal_long(ap, flag, str);
	else if (c == 'U')
		length = arg_putnbr_un_long(ap, flag, str);
	else if (c == 'C')
		length = arg_putwchar(ap, flag, str);
	return (length);
}
