/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 14:56:36 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 15:23:16 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putstr2(char *str, int length)
{
	int		i;

	i = 0;
	while (i < length)
	{
		ft_putchar(str[i]);
		i++;
	}
}

void		prepend_plus_space_flags(char **value, t_format *format_var, int *length)
{
	char	*tmp;

	if ((format_var->plus_flag || format_var->space_flag) && !format_var->neg_val)
	{
		format_var->has_sign = 1;
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 2))))
		{
			tmp[*length + 1] = '\0';
			tmp[0] = (format_var->plus_flag ? '+' : ' ');
			ft_memcpy(tmp + 1, *value, *length);
			free(*value);
			*value = tmp;
			(*length)++;
		}
		else
			*value = NULL;
	}
}

int			get_decal(t_format *format)
{
	int		decal;

	decal = (format->specifier == 'p' && format->char_to_fill == '0' ? 2 : 0);
	if (format->char_to_fill == '0' && decal == 0 && format->sharp_flag == 1)
	{
		if (format->specifier == 'o' || format->specifier == 'O')
			decal = 1;
		else if (format->specifier == 'x' || format->specifier == 'X')
			decal = 2;
	}
	return (decal);
}

int			print_format(t_format *format, va_list ap)
{
	char	*value;
	int		length;
	int		decal;
	int		o_done;

	o_done = 0;
	decal = get_decal(format);
	length = get_arg(&value, ap, format);
	if (format->neg_val == 1)
		format->has_sign = 1;
	if (format->specifier == 'd' || format->specifier == 'D'
			|| format->specifier == 'i' || format->specifier == 'b'
			|| format->specifier == 'f' || format->specifier == 'F')
		prepend_plus_space_flags(&value, format, &length);
	if (format->sharp_flag && (format->specifier == 'o' || format->specifier == 'O') && format->precision != 0)
	{
		o_done = 1;
		add_prefix_for_addresses_n_sharp(&value, format, &length);
	}
	if (is_valid_specifier(format->specifier))
		append_precision_to_value(&value, format, &length, 1);
	if (!format->minus_flag)
	{
		if (!o_done && format->char_to_fill == ' ')
			add_prefix_for_addresses_n_sharp(&value, format, &length);
		ajust_value_to_width(&value, format, &length, decal);
		if (!o_done && format->char_to_fill == '0')
			add_prefix_for_addresses_n_sharp(&value, format, &length);
	}
	else
	{
		if (!o_done)
			add_prefix_for_addresses_n_sharp(&value, format, &length);
		ajust_value_to_width_minus(&value, format, &length);
	}
	ft_putstr2(value, length);
	if (value)
		free(value);
	value = NULL;
	return (length);
}
