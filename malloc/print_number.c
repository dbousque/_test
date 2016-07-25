

#include "malloc.h"

void	print_number(size_t number)
{
	char	numbers[100];
	int		ind;

	if (number == 0)
	{
		write(1, "0", 1);
		return ;
	}
	ind = 99;
	while (number > 0)
	{
		numbers[ind] = (number % 10) + '0';
		number /= 10;
		ind--;
	}
	ind++;
	while (ind < 100)
	{
		write(1, numbers + ind, 1);
		ind++;
	}
}


void	print_address(void *ptr)
{
	write(1, "0x", 2);	
	print_ft_ntoa_base((size_t)ptr, "0123456789ABCDEF");
}

void	print_byte(void *ptr)
{
	print_ft_ntoa_base(*((char*)ptr), "0123456789abcdef");
}