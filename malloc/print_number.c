

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


#  include <stdio.h>




void	print_address(void *ptr)
{
	printf("%p", ptr);
	fflush(stdout);
}