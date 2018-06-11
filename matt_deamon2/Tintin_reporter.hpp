

#ifndef TINTIN_REPORTER_H
# define TINTIN_REPORTER_H


# include <unistd.h>
# include <sys/file.h>
# include <stdio.h>
# include <time.h>

# define MAX_NB_CLIENTS 3

enum log_type {
	LOG,
	INFO,
	ERROR
};

class Tintin_reporter
{
	public:
		Tintin_reporter(int log_file_fd);
		Tintin_reporter(Tintin_reporter &other);
		virtual ~Tintin_reporter();

		Tintin_reporter		&operator=(Tintin_reporter &other);

		bool				log(char *msg, log_type type);

	private:
		Tintin_reporter();
		bool	try_reopen_log_file(void);
		bool	try_write(char *msg);
		int		_log_file_fd;
		int		_failed_write;
};

#endif