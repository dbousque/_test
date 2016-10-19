

#include <stdio.h>

int		main(void)
{
	char 	*lol = "salut";
	printf("%p\n", lol);
	printf("\x82\x2f\x06\x00_%08x.%08x.%08x.%08x.%08x|%s|");
	return (0);
}
