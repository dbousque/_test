

#include "ft_printf.h"



#include <stdio.h>

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

int		put_min_width(int min_width, int length, char char_to_fill)
{
	int		nb;
	int		added;

	nb = (min_width > 0 ? min_width - length : -min_width - length);
	added = nb;
	while (nb > 0)
	{
		ft_putchar(char_to_fill);
		nb--;
	}
	return (added);
}

int		print_arg(char c, va_list ap, int *i, char flag, int min_width, char char_to_fill, char prefix, char show_sign)
{
	int		length;
	char	*str;
	int		added_chars;

	(*i)++;
	length = 0;
	added_chars = 0;
	str = NULL;
	if (c == 'd' || c == 'i')
		length = arg_putnbr(ap, flag, &str);
	else if (c == 'c')
		length = arg_putchar(ap, flag, &str);
	else if (c == 's')
		length = arg_putstr(ap, flag, &str);
	else if (c == 'u')
		length = arg_putnbr_un(ap, flag, &str);
	else if (c == 'p')
		length = arg_putaddr(ap, flag, &str);
	else if (c == 'o')
		length = arg_putoctal(ap, flag, &str);
	else if (c == 'x')
		length = arg_puthexa(ap, flag, &str);
	else if (c == 'X')
		length = arg_puthexa_maj(ap, flag, &str);
	else if (c == 'S')
		length = arg_putunicode(ap, flag, &str);
	else if (c == 'D')
		length = arg_putnbr_long(ap, flag, &str);
	else if (c == 'O')
		length = arg_putoctal_long(ap, flag, &str);
	else if (c == 'U')
		length = arg_putnbr_un_long(ap, flag, &str);
	else if (c == 'C')
		length = arg_putwchar(ap, flag, &str);
	if (str && (str[0] == '-' || show_sign))
	{
		if (str[0] == '-')
		{
			ft_putchar('-');
			str++;
		}
		else
		{
			length++;
			if (show_sign == -1)
				ft_putchar(' ');
			else
				ft_putchar('+');
		}
	}
	if (str && length < min_width)
		added_chars = put_min_width(min_width, length, char_to_fill);
	if (str && prefix && !(str[0] == '0' && ft_strlen(str) == 1))
	{
		ft_putchar('0');
		length++;
		if (c == 'x')
		{
			ft_putchar('x');
			length++;
		}
		else if (c == 'X')
		{
			ft_putchar('X');
			length++;
		}
	}
	if (str)
		ft_putstr(str);
	if (str && min_width < 0 && -min_width > length)
		added_chars = put_min_width(min_width, length, char_to_fill);
	return (length + added_chars);
}

int		ft_intlen(int nb)
{
	int		length;

	if (nb == 0)
		return (1);
	length = 0;
	while (nb != 0)
	{
		length++;
		nb /= 10;
	}
	return (length);
}

int		get_min_width(const char *format, int *i, char *char_to_fill, char *prefix, char *show_sign)
{
	int		res;
	int		neg;

	res = 0;
	neg = 0;
	if (format[*i + 1] == '-')
	{
		neg = 1;
		(*i)++;
	}
	else if (format[*i + 1] == '0')
	{
		*char_to_fill = '0';
		(*i)++;
	}
	else if (format[*i + 1] == '#')
	{
		*prefix = 1;
		(*i)++;
	}
	else if (format[*i + 1] == '+')
	{
		*show_sign = 1;
		(*i)++;
	}
	else if (format[*i + 1] == ' ')
	{
		*show_sign = -1;
		(*i)++;
	}
	if (format[*i + 1] > '0' && format[*i + 1] <= '9')
		res = ft_atoi(format + *i + 1);
	if (res != 0)
		*i += ft_intlen(res);
	if (neg == 1)
		return (-res);
	return (res);
}

char	get_flag(const char *format, int *i, int *min_width, char *char_to_fill, char *prefix, char *show_sign)
{
	char	res;

	res = NO_FLAG;
	*min_width = get_min_width(format, i, char_to_fill, prefix, show_sign);
	if (!format[*i + 1])
		res = NO_FLAG;
	else if (format[*i + 1] == 'h' && format[*i + 2] == 'h')
		res = HH;
	else if (format[*i + 1] == 'h')
		res = H;
	else if (format[*i + 1] == 'l' && format[*i + 2] == 'l')
		res = LL;
	else if (format[*i + 1] == 'l')
		res = L;
	else if (format[*i + 1] == 'j')
		res = J;
	else if (format[*i + 1] == 'z')
		res = Z;
	if (res == HH || res == LL)
		*i += 2;
	else if (res != NO_FLAG)
		*i += 1;
	return (res);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	char	flag;
	int		length;
	int		min_width;
	char	char_to_fill;
	char	prefix;
	char	show_sign;

	show_sign = 0;
	prefix = 0;
	char_to_fill = ' ';
	length = 0;
	if (format)
		va_start(ap, format);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if ((flag = get_flag(format, &i, &min_width, &char_to_fill, &prefix, &show_sign)) == NO_FLAG)
				length += print_arg(format[i + 1], ap, &i, NO_FLAG, min_width, char_to_fill, prefix, show_sign);
			else
				length += print_arg(format[i + 1], ap, &i, flag, min_width, char_to_fill, prefix, show_sign);
		}
		else
		{
			if (format[i] == '%')
				i++;
			ft_putchar(format[i]);
			length++;
		}
		i++;
	}
	return (length);
}

int		main(int argc, char **argv)
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
	inp = "lol : %hhd, %c, %s, %u, %p, %lO, %X, %llu\n";
	nb = (unsigned long long)-200000000000;
	nb2 = 0;
	i = -1;
	long_int = 990000000000000000;
	lol2 = NULL;
	(void)lol;
	printf("%d\n", printf("{%+o}", 0));
	printf("%d\n", ft_printf("{%+o}", 0));
	//printf("%-18p\n", &i);
	//ft_printf("%-18p\n", &i);
	//ft_printf("1 : %S\n", L"saluté");//L"米");
	//printf("2 : %S\n", L"saluté");
	//ft_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S",
	//L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	//L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	//ft_printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	//printf(inp, nb, -200, 0, -150, 0, -1, 260, long_int);
	return (0);
}
