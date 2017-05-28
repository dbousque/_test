

#include "shared_ressources.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_shared	shared;
	char		creation;
	int		*entier;

	creation = 0;
	init_shared(&shared, "salut");
	add_shared_ressource(&shared, 42, sizeof(int), &creation);
	if (creation)
	{
		entier = (int*)get_shared_ressource(&shared, 42, &creation);
		*entier = 0;
	}
	else
		entier = (int*)get_shared_ressource(&shared, 42, &creation);
	if (argc <= 1)
	{
		while (1)
		{
			sleep(1);
			*entier = *entier + 1;
		}
	}
	else
	{
		while (1)
		{
			sleep(1);
			printf("entier : %d\n", *entier);
		}
	}
	return (0);
}
