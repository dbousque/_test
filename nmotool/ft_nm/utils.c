

#include "nm.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putstrnl(char *str)
{
	ft_putstr(str);
	write(1, "\n", 1);
}

void	print_error(char *str)
{
	ft_putstr("\033[91m");
	ft_putstr("[ERROR] ");
	ft_putstr("\033[0m");
	ft_putstrnl(str);
}

void	print_error_file(char *str, char *filename)
{
	ft_putstr("\033[91m");
	ft_putstr("[ERROR] ");
	ft_putstr("\033[0m");
	ft_putstr(filename);
	ft_putstr(" : ");
	ft_putstrnl(str);
}

void	print_format(void)
{
	print_error("Bad format. Expected \"ft_nm <filename1> [<filename2] [...]\"");
}