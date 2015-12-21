

#include "ft_printf.h"

int		ft_putaddr(void *addr, char long_long, char **str)
{
	long long	value;
	char		*res;

	value = (long_long ? (long long)addr : (long)addr);
	res = ft_ntoa_base(value, "0123456789abcdef");
	if (res)
	{
		*str = (char*)malloc(sizeof(char) * (ft_strlen(res) + 3));
		(*str)[0] = '0';
		(*str)[1] = 'x';
		strcpy(*str + 2, res);
	}
	else
		*str = ft_strdup("0");
	return (ft_strlen(*str));
}

int		ft_putaddr_un(void *addr, char long_long, char **str)
{
	unsigned long long	value;
	char				*res;

	value = (long_long ? (unsigned long long)addr : (unsigned long)addr);
	res = ft_ntoa_base_un(value, "0123456789abcdef");
	if (res)
	{
		*str = (char*)malloc(sizeof(char) * (ft_strlen(res) + 3));
		(*str)[0] = '0';
		(*str)[1] = 'x';
		strcpy(*str + 2, res);
	}
	else
		*str = ft_strdup("0");
	return (ft_strlen(*str));
}
