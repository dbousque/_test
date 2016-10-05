

#include "Logger.hpp"
#include <ctime>
#include <iostream>
#include <fstream>

Logger::Logger(std::string filename) :
	_filename(filename)
{
}

Logger::~Logger()
{
}

std::string	Logger::makeLogEntry(std::string msg) const
{
	time_t const	t = time(0);
	std::string		time_str = std::string(ctime(&t));

	return "[" + time_str.substr(0, time_str.length() - 1) + "] " + msg;
}

void	Logger::logToConsole(std::string msg) const
{
	std::cout << msg << std::endl;
}

void	Logger::logToFile(std::string msg) const
{
	std::ofstream	ofs(this->_filename, std::ofstream::ate | std::ofstream::app);

	ofs << msg << std::endl;
	ofs.close();
}

int		index_of(std::string *array, std::string const &to_find, int len)
{
	int		i;

	i = 0;
	while (i < len && array[i] != to_find)
		i++;
	return (i);
}

void	Logger::log(std::string const & dest, std::string const & msg)
{
	std::string	names[2] = {"logToConsole", "logToFile"};
	void	(Logger::*log_funcs[2])(std::string msg) const = {&Logger::logToConsole, &Logger::logToFile};
	void	(Logger::*log_func)(std::string msg) const;
	int		ind;

	ind = index_of(names, dest, 2);
	if (ind != 2)
	{
		log_func = log_funcs[ind];
		(this->*log_func)(this->makeLogEntry(msg));
	}
}
