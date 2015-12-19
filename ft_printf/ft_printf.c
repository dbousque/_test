

#include "ft_printf.h"



#include <stdio.h>

int		arg_putnbr(va_list ap, char flag)
{
	int		res;
	long	res2;
	int		length;

	if (flag == L)
	{
		res2 = va_arg(ap, long);
		length = ft_putlong(res2);
	}
	else
	{
		res = va_arg(ap, int);
		length = ft_putlong(res);
	}
	return (length);
}

int		arg_putnbr_long(va_list ap, char flag)
{
	long		res;
	long long	res2;
	int			length;

	if (flag == L)
	{
		res2 = va_arg(ap, long long);
		length = ft_putlong(res2);
	}
	else
	{
		res = va_arg(ap, long);
		length = ft_putlong(res);
	}
	return (length);
}

int		arg_putnbr_un(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;
	int				length;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		length = ft_putlong_un(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		length = ft_putnbr_un(res);
	}
	return (length);
}

int		arg_putnbr_un_long(va_list ap, char flag)
{
	unsigned long		res;
	unsigned long long	res2;
	int					length;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long long);
		length = ft_putlong_un(res2);
	}
	else
	{
		res = va_arg(ap, unsigned long);
		length = ft_putlong_un(res);
	}
	return (length);
}

int		arg_putchar(va_list ap, char flag)
{
	char	res;
(void)flag;
	res = va_arg(ap, int);
	ft_putchar((unsigned char)res);
	return (1);
}

int		arg_putunicode(va_list ap, char flag)
{
	wchar_t	*res;
(void)flag;
	res = va_arg(ap, wchar_t*);
	if (res)
		ft_putunicode(res);
	else
	{
		ft_putstr("(null)");
		return (6);
	}
	return (ft_unicodelen(res));
}

int		arg_putstr(va_list ap, char flag)
{
	char	*res;

	if (flag == L)
		return (arg_putunicode(ap, flag));
	res = va_arg(ap, char*);
	if (res)
		ft_putstr(res);
	else
	{
		ft_putstr("(null)");
		return (6);
	}
	return (ft_strlen(res));
}

int		arg_putaddr(va_list ap, char flag)
{
	void	*res;
	int		length;

	if (flag == L)
	{
		res = va_arg(ap, void*);
		length = ft_putaddr_un(res, 1);
	}
	else
	{
		res = va_arg(ap, void*);
		length = ft_putaddr(res, 1);
	}
	return (length);
}

int		arg_putoctal(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;
	int				length;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		length = ft_putoctal_un(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		length = ft_putoctal_un(res);
	}
	return (length);
}

int		arg_putoctal_long(va_list ap, char flag)
{
	unsigned long		res;
	unsigned long long	res2;
	int					length;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long long);
		length = ft_putoctal_un(res2);
	}
	else
	{
		res = va_arg(ap, unsigned long);
		length = ft_putoctal_un(res);
	}
	return (length);
}

int		arg_puthexa(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;
	int				length;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		length = ft_puthexa(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		length = ft_puthexa(res);
	}
	return (length);
}

int		arg_puthexa_maj(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;
	int				length;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		length = ft_puthexa_maj(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		length = ft_puthexa_maj(res);
	}
	return (length);
}

int		print_arg(char c, va_list ap, int *i, char flag)
{
	int		length;

	(*i)++;
	length = 0;
	if (c == 'd' || c == 'i')
		length = arg_putnbr(ap, flag);
	else if (c == 'c')
		length = arg_putchar(ap, flag);
	else if (c == 's')
		length = arg_putstr(ap, flag);
	else if (c == 'u')
		length = arg_putnbr_un(ap, flag);
	else if (c == 'p')
		length = arg_putaddr(ap, flag);
	else if (c == 'o')
		length = arg_putoctal(ap, flag);
	else if (c == 'x')
		length = arg_puthexa(ap, flag);
	else if (c == 'X')
		length = arg_puthexa_maj(ap, flag);
	else if (c == 'S')
		length = arg_putunicode(ap, flag);
	else if (c == 'D')
		length = arg_putnbr_long(ap, flag);
	else if (c == 'O')
		length = arg_putoctal_long(ap, flag);
	else if (c == 'U')
		length = arg_putnbr_un_long(ap, flag);
	return (length);
}

char	get_flag(const char *format, int *i)
{
	char	res;

	res = NO_FLAG;
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

	length = 0;
	if (format)
		va_start(ap, format);
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%' && format[i + 1] != '%')
		{
			if ((flag = get_flag(format, &i)) == NO_FLAG)
				length += print_arg(format[i + 1], ap, &i, NO_FLAG);
			else
				length += print_arg(format[i + 1], ap, &i, flag);
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
	int				nb;
	unsigned int	nb2;
	char			*inp;
	int				i;
	wchar_t			*lol = L"ру́сский";
	char			*lol2 = "salut";

	(void)argc;
	(void)argv;
	inp = "lol : %d, %c, %s, %u, %p, %o, %X, %u, %S\n";
	nb = -2;
	nb2 = 0;
	i = -1;
	(void)lol2;
	(void)lol;
	ft_printf("%lx\n", 140734725794680);
	printf("%lx\n", 140734725794680);
	//ft_printf("1 : %S\n", L"米");
	//printf("2 : %S\n", L"米");
	//ft_printf(inp, nb, -200, 0, -150, 0, -1, -127, 21400000000, lol);
	//printf(inp, nb, -200, 0, -150, 0, -1, -127, 21400000000, lol);
	return (0);
}
