

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

void	read_from_stdin(void)
{
	pid_t	pid = fork();

	if (pid == 0)
	{
		std::string	line;

		while (getline(std::cin, line))
			std::cout << line << std::endl;
	}
	else
		wait(NULL);
}

bool	file_exist(std::string filename)
{
	std::ifstream	ifs(filename);
	bool			res;

	res = ifs.good();
	ifs.close();
	return (res);
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
	if (!file_exist(filename))
	{
		std::cout << filename << " : No such file" << std::endl;
		return ;
	}
	std::ifstream	ifs(filename);
	char			chars[256 + 1];

	while (ifs.read(chars, 256))
	{
		chars[ifs.gcount()] = '\0';
		std::cout << chars;
	}
	chars[ifs.gcount()] = '\0';
	std::cout << chars;
	ifs.close();
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		read_from_stdin();
	else
	{
		for (int i=1; i < argc; i++)
		{
			if (strncmp(argv[i], "-", 5) == 0)
				read_from_stdin();
			else
				read_file(argv[i]);
		}
	}
	return (0);
}