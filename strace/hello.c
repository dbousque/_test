

#include <unistd.h>

int	main(void)
{
	int i = 0;
	while (i < 1)
	{
		write(1, "salut", 5);
		i++;
	}
	//sleep(2);
	return (0);
}
