/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:54:11 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 17:22:35 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		cut_digits(char **value, t_format *format, int *length)
{
	int		ind;
	char	*tmp;

	ind = 0;
	while (*value && (*value)[ind] && (*value)[ind] != '.')
		ind++;
	if ((*value)[ind] == '.')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (ind + format->precision + 2))))
		{
			tmp = ft_strncpy(tmp, *value, ind + format->precision + 1);
			tmp[ind + format->precision + 1] = '\0';
			free(*value);
			*value = tmp;
			*length = ind + 1 + format->precision;
		}
		else
			*value = NULL;
	}
}

char		is_spec_numb(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'o' || c == 'O' || c == 'u'
		|| c == 'U' || c == 'x' || c == 'X' || c == 'p' || c == 'b' || c == 'f'
		|| c == 'F')
		return (1);
	return (0);
}

void		append_precision_to_value(char **value, t_format *format, int *length, char ori)
{
	char	*tmp;
	int		val_len;
	int		val_len_without_sign;
	int		res_len;
	int		i;
	int		x;

	if (ori && format->precision > 0 && (format->specifier == 'f' || format->specifier == 'F'))
		cut_digits(value, format, length);
	else if (is_other_maj(format->specifier) || is_spec_numb(format->specifier))
	{
		if (!is_other_maj(format->specifier) && format->precision == 0 && ((format->unsigned_val && format->u_value == 0) || (format->unsigned_val == 0 && format->value == 0)))
		{
			free(*value);
			*value = (char*)malloc(sizeof(char));
			(*value)[0] = '\0';
			*length = 0;
		}
		else
		{
			val_len = *length;
			val_len_without_sign = (format->has_sign ? val_len - 1 : val_len);
			if (format->precision > val_len_without_sign)
			{
				res_len = format->precision + (val_len - val_len_without_sign);
				*length += res_len - val_len;
				if ((tmp = (char*)malloc(sizeof(char) * (format->precision + res_len + 1))))
				{
					tmp[res_len] = '\0';
					i = 0;
					if (format->neg_val == 1 || format->has_sign)
					{
						tmp[0] = (*value)[0];
						i = 1;
					}
					x = i;
					while (i < res_len - val_len_without_sign)
					{
						tmp[i] = '0';
						i++;
					}
					while (i < res_len)
					{
						tmp[i] = (*value)[x];
						i++;
						x++;
					}
					free(*value);
					*value = tmp;
				}
			}
		}
	}
	else if ((format->specifier == 'r' || format->specifier == 's' || format->specifier == 'S') && format->precision >= 0 && format->precision < (int)ft_strlen(*value))
	{
		if ((tmp = (char*)malloc(sizeof(char) * format->precision + 1)))
		{
			tmp[format->precision] = '\0';
			tmp = ft_strncpy(tmp, *value, format->precision);
			free(*value);
			*value = tmp;
			*length = format->precision;
		}
	}
}

void		ajust_value_to_width_minus(char **value, t_format *format_var, int *length)
{
	char	*tmp;

	if (format_var->width > *length)
	{
		if ((tmp = (char*)malloc(sizeof(char) * (format_var->width + 1))))
		{
			tmp[format_var->width] = '\0';
			ft_memcpy(tmp, *value, *length);
			while (*length < format_var->width)
			{
				tmp[*length] = ' ';
				(*length)++;
			}
			free(*value);
			*value = tmp;
		}
		else
			*value = NULL;
	}
}

void		ajust_value_to_width(char **value, t_format *format_var, int *length, int decal)
{
	int		val_len;
	int		ori_precision;
	char	ori_specifier;
	char	*tmp;
	int		i;

	val_len = *length + decal;
	if (format_var->width > val_len)
	{
		if (format_var->char_to_fill == '0')
		{
			ori_precision = format_var->precision;
			ori_specifier = format_var->specifier;
			if (format_var->has_sign == 1)
				format_var->precision = format_var->width - 1;
			else
				format_var->precision = format_var->width;
			format_var->precision -= decal;
			format_var->specifier = 'd';
			append_precision_to_value(value, format_var, length, 0);
			format_var->precision = ori_precision;
			format_var->specifier = ori_specifier;
		}
		else
		{
			if ((tmp = (char*)malloc(sizeof(char) * (format_var->width + 1))))
			{
				tmp[format_var->width] = '\0';
				i = val_len;
				while (val_len < format_var->width)
				{
					tmp[val_len - i] = ' ';
					val_len++;
					(*length)++;
				}
				ft_memcpy(tmp + (val_len - i), *value, format_var->width - (val_len - i));
				free(*value);
				*value = tmp;
			}
			else
				*value = NULL;
		}
	}
}

void		add_sharp_prefix(char **value, t_format *format_var, int *length)
{
	char	*tmp;

	if (format_var->specifier == 'o' || format_var->specifier == 'O')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 2))))
		{
			tmp[*length + 1] = '\0';
			(*length)++;
			tmp[0] = '0';
			ft_strcpy(tmp + 1, *value);
			free(*value);
			*value = tmp;
		}
		else
			*value = NULL;
	}
	else if (format_var->specifier == 'x' || format_var->specifier == 'X')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 3))))
		{
			tmp[*length + 2] = '\0';
			(*length) += 2;
			tmp[0] = '0';
			tmp[1] = (format_var->specifier == 'x' ? 'x' : 'X');
			ft_strcpy(tmp + 2, *value);
			free(*value);
			*value = tmp;
		}
		else
			*value = NULL;
	}
}

void		add_prefix_for_addresses_n_sharp(char **value, t_format *format_var, int *length)
{
	char	*tmp;
	int		len;

	if (format_var->specifier == 'p')
	{
		len = ft_strlen(*value);
		if ((tmp = (char*)malloc(sizeof(char) * (len + 1))))
		{
			tmp[len] = '\0';
			tmp[0] = '0';
			tmp[1] = 'x';
			ft_strcpy(tmp + 2, *value);
			free(*value);
			*value = tmp;
			*length += 2;
		}
		else
			*value = NULL;
	}
	else if (format_var->sharp_flag == 1 && (format_var->u_value != 0 || (format_var->precision != -1 && format_var->specifier != 'x')))
		add_sharp_prefix(value, format_var, length);
}

void		free_format(t_format *format)
{
	if (format)
		free(format);
	format = NULL;
}

t_format	*new_format(void)
{
	t_format	*format_var;

	if (!(format_var = (t_format*)malloc(sizeof(t_format))))
		return (NULL);
	format_var->char_to_fill = ' ';
	format_var->neg_val = 0;
	format_var->unsigned_val = 0;
	format_var->has_sign = 0;
	format_var->characters = 0;
	format_var->length = -1;
	format_var->width = -1;
	format_var->precision = -1;
	format_var->specifier = -1;
	format_var->plus_flag = 0;
	format_var->sharp_flag = 0;
	format_var->space_flag = 0;
	format_var->minus_flag = 0;
	format_var->value = 0;
	format_var->u_value = 0;
	return (format_var);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	int			length;
	t_format	*format_var;

	length = 0;
	if (format)
		va_start(ap, format);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '{')
			ft_change_color_if_asked(format, &i);
		if (format[i] == '%' && format[i + 1] != '%')
		{
			format_var = new_format();
			if (parse_format(format, format_var, &i, ap) != -1)
				length += print_format(format_var, ap);
			else
				i--;
			if (format_var)
				free_format(format_var);
		}
		else
		{
			if (format[i] == '%')
				i++;
			if (format[i])
			{
				ft_putchar(format[i]);
				length++;
			}
		}
		if (format[i])
			i++;
	}
	return (length);
}

/*int		main(int argc, char **argv)
{
	unsigned long long			nb;
	unsigned long long	nb2;
	char			*inp;
	int				i;
	wchar_t			*lol = L"ру́сский";
	char			*lol2 = "salut";
	long long		long_int;

	(void)argc;
	(void)argv;
	inp = (char*)malloc(sizeof(char) * 8);
	inp[7] = '\0';
	inp[0] = 'a';
	inp[1] = 23;
	inp[2] = 27;
	inp[3] = 'b';
	inp[4] = 12;
	inp[5] = 4;
	inp[6] = 'c';
	nb = (unsigned long long)-200000000000;
	nb2 = 0;
	i = -1;
	long_int = 990000000000000000;
	lol2 = NULL;
	(void)lol;
	printf("%d\n", printf("{%-+.4f}{%F}", -12.4, 1444565444646.6465424242242));
	printf("%d\n", ft_printf("{%.4f}{%F}", -12.4, 1444565444646.6465424242242));
	//printf("%d\n", printf("{%15.4d}", -424242));
	//printf("%d\n", ft_printf("{%15.4d}", -424242));
	//printf("%-18p\n", &i);
	//ft_printf("%-18p\n", &i);
	//ft_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",
	//L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	//L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	//ft_printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	//printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	return (0);
}*/
