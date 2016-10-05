

#include "Logger.hpp"
#include <iostream>

int		main(void)
{
	Logger	log = Logger("log_out");

	std::cout << "Logging some stuff on stdout and in file \"log_out\"" << std::endl;
	
	log.log("logToConsole", "first log");
	log.log("logToFile", "first log");

	log.log("logToConsole", "second");
	log.log("logToFile", "second");

	log.log("logToConsole", "the next one is empty");
	log.log("logToFile", "the next one is empty");

	log.log("logToConsole", "");
	log.log("logToFile", "");

	log.log("logToConsole", "some non-ascii characters : éàî 字");
	log.log("logToFile", "some non-ascii characters : éàî 字");

	log.log("logToConsole", "last log");
	log.log("logToFile", "last log");
	return (0);
}