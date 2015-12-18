

#include "ft_printf.h"



#include <stdio.h>

void	arg_putnbr(va_list ap, char flag)
{
	int		res;
	long	res2;

	if (flag == L)
	{
		res2 = va_arg(ap, long);
		ft_putlong(res2);
	}
	else
	{
		res = va_arg(ap, int);
		ft_putnbr(res);
	}
}

void	arg_putnbr_un(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		ft_putlong_un(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		ft_putnbr_un(res);
	}
}

void	arg_putchar(va_list ap, char flag)
{
	char	res;
(void)flag;
	res = va_arg(ap, int);
	ft_putchar((unsigned char)res);
}

void	arg_putstr(va_list ap, char flag)
{
	char	*res;
(void)flag;
	res = va_arg(ap, char*);
	ft_putstr(res);
}

void	arg_putaddr(va_list ap, char flag)
{
	void	*res;

	if (flag == L)
	{
		res = va_arg(ap, void*);
		ft_putaddr_un(res);
	}
	else
	{
		res = va_arg(ap, void*);
		ft_putaddr(res);
	}
}

void	arg_putoctal(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		ft_putoctal_un(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		ft_putoctal_un(res);
	}
}

void	arg_puthexa(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		ft_puthexa(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		ft_puthexa(res);
	}
}

void	arg_puthexa_maj(va_list ap, char flag)
{
	unsigned int	res;
	unsigned long	res2;

	if (flag == L)
	{
		res2 = va_arg(ap, unsigned long);
		ft_puthexa_maj(res2);
	}
	else
	{
		res = va_arg(ap, unsigned int);
		ft_puthexa_maj(res);
	}

}

void	print_arg(char c, va_list ap, int *i, char flag)
{
	(*i)++;
	if (c == 'd' || c == 'i')
		arg_putnbr(ap, flag);
	else if (c == 'c')
		arg_putchar(ap, flag);
	else if (c == 's')
		arg_putstr(ap, flag);
	else if (c == 'u')
		arg_putnbr_un(ap, flag);
	else if (c == 'p')
		arg_putaddr(ap, flag);
	else if (c == 'o')
		arg_putoctal(ap, flag);
	else if (c == 'x')
		arg_puthexa(ap, flag);
	else if (c == 'X')
		arg_puthexa_maj(ap, flag);

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

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if ((flag = get_flag(format, &i)) == NO_FLAG)
				print_arg(format[i + 1], ap, &i, NO_FLAG);
			else
				print_arg(format[i + 1], ap, &i, flag);
		}
		else
			ft_putchar(format[i]);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int				nb;
	unsigned int	nb2;
	char			*inp;

	(void)argc;
	(void)argv;
	inp = "lol : %ld, %c, %lu, %lp, %lo, %lX, %lu\n";
	nb = -2;
	nb2 = 0;
	ft_printf(inp, nb, -200, -150, inp, -1, -127, 21400000000);
	printf(inp, nb, -200, -150, inp, -1, -127, 21400000000);
}
