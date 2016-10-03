

#include <iostream>

char	*str_toupper(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = toupper(str[i]);
		i++;
	}
	return (str);
}

int		main(int argc, char **argv)
{
	int		i;

	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		i = 1;
		while (i < argc)
		{
			std::cout << str_toupper(argv[i]);
			i++;
		}
	}
	std::cout << std::endl;
	return (0);
}
