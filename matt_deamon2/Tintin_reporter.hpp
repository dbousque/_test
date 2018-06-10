

#ifndef TINTIN_REPORTER_H
# define TINTIN_REPORTER_H

# include <string>
# include <iostream>
# include <fstream>
# include <unistd.h>
# include <sys/file.h>
# include <time.h>
# include <arpa/inet.h>

# define MAX_NB_CLIENTS 3

enum log_type {
	LOG,
	INFO,
	ERROR
};

class Tintin_reporter
{
	public:
		Tintin_reporter(int lock_file_fd, int log_file_fd, int server_fd);
		Tintin_reporter(Tintin_reporter &other);
		virtual ~Tintin_reporter();

		Tintin_reporter		&operator=(Tintin_reporter &other);

		bool				log(char *msg, log_type type);

	private:
		Tintin_reporter();
		void	run_server(void);
		bool	accept_client(int server_fd, int *clients, int *nb_clients);
		bool	read_and_log_client_input(int i, int *clients, int *nb_clients);
		bool	try_reopen_log_file(void);
		bool	try_write(char *msg);
		int		_lock_file_fd;
		int		_log_file_fd;
		int		_server_fd;
		int		_failed_write;
};

#endif