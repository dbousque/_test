

#ifndef LOGGER_H
# define LOGGER_H

#include <string>

class Logger
{
	public:
		Logger(std::string filename);
		~Logger();
		void				log(std::string const & dest, std::string const & message);

	private:
		std::string const	_filename;
		void				logToConsole(std::string str) const;
		void				logToFile(std::string str) const;
		std::string			makeLogEntry(std::string str) const;
};

#endif