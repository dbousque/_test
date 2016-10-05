

#include <iostream>
#include <fstream>
#include <string>

void	read_from_stdin(void)
{
	std::string	line;

	while (getline(std::cin, line))
		std::cout << line << std::endl;
}

std::streampos	get_file_size(std::string filename)
{
	std::streampos	res;
	std::ifstream	ifs(filename, std::ifstream::ate | std::ifstream::binary);

	res = ifs.tellg();
	ifs.close();
	return (res);
}

void	read_file(std::string filename)
{
	size_t	file_size;
	
	file_size = get_file_size(filename);
	//if (file_size < 0)
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		read_from_stdin();
	else
	{
		for (int i=0; i < argc; i++)
		{
			if (strncmp(argv[i], "-", 5))
				read_from_stdin();
			else
				read_file(argv[i]);
		}
	}
	return (0);
}