

#include <iostream>
#include <unistd.h>
#include <fstream>

int		bad_format(void)
{
	std::cout << "Format ./replace <filename> <str_to_replace> <str_replace_by>" << std::endl;
	return (0);
}

bool	bad_file(std::string filename)
{
	std::cout << "File \"" << filename << "\" is either too small or has no size (0 bytes), or could not be opened" << std::endl;
	return (true);
}

bool	file_too_big(std::string filename)
{
	std::cout << "File \"" << filename << "\" is too big" << std::endl;
	return (true);
}

long long	get_available_memory()
{
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return (pages * page_size);
}

bool	empty_strs(int argc, char **argv)
{
	for (int i = 2; i < argc; i++)
	{
		if (strlen(argv[i]) == 0)
			return (true);
	}
	return (false);
}

std::streampos	get_file_size(std::string filename)
{
	std::streampos	res;
	std::ifstream	ifs(filename, std::ifstream::ate | std::ifstream::binary);

	res = ifs.tellg();
	ifs.close();
	return (res);
}

bool	check_file_error(std::string filename, std::streampos size)
{
	if (size <= 0)
		return (bad_file(filename));
	// need to keep at least half of the memory available
	if (size > get_available_memory() / 2)
		return (file_too_big(filename));
	return (false);
}

void	replace_substring(std::string filename, std::string &inp, std::string to_rep, std::string rep_by)
{
	size_t			index;
	size_t			tmp_index;
	std::ofstream	ofs(filename + ".replace");

	index = 0;
	while (true)
	{
		tmp_index = inp.find(to_rep, index);
		//std::cout << std::endl << "Index : " << tmp_index << std::endl;
		if (tmp_index == std::string::npos)
		{
			ofs << inp.substr(index, inp.length() - index);
			break ;
		}
		ofs << inp.substr(index, tmp_index - index);
		ofs << rep_by;
		index = tmp_index + to_rep.length();
	}
	ofs.close();
}

void	replace(std::string filename, std::string to_rep, std::string rep_by)
{
	std::streampos	size;

	size = get_file_size(filename);
	if (check_file_error(filename, size))
		return ;
	std::ifstream	ifs(filename);
	char			*tmp_file_content;

	tmp_file_content = new char[size];
	ifs.read(tmp_file_content, size);
	std::string		file_content = std::string(tmp_file_content);
	if (file_content.length() > 0)
		replace_substring(filename, file_content, to_rep, rep_by);
	delete tmp_file_content;
}

int		main(int argc, char **argv)
{
	if (argc != 4)
		return (bad_format());
	if (empty_strs(argc, argv))
		return (bad_format());
	replace(argv[1], argv[2], argv[3]);
	return (0);
}
