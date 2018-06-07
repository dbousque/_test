

#ifndef TINTIN_REPORTER_H
# define TINTIN_REPORTER_H

# include <string>
# include <iostream>
# include <fstream>
# include <unistd.h>
# include <sys/file.h>
# include <netdb.h>
# include <netinet/in.h>

class Tintin_reporter
{
	public:
		Tintin_reporter();
		Tintin_reporter(Tintin_reporter &other);
		virtual ~Tintin_reporter();

		Tintin_reporter		&operator=(Tintin_reporter &other);

	//private:
		//Tintin_reporter();
};

std::ostream	&operator<<(std::ostream &os, Tintin_reporter &reporter);
int				create_server(int port);

#endif