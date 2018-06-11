

#ifndef MATT_DAEMON_H
# define MATT_DAEMON_H

# include <unistd.h>
# include <sys/file.h>
# include <netdb.h>
# include <netinet/in.h>
# include <signal.h>
# include <stdio.h>
# include <iostream>
# include "Tintin_reporter.hpp"

# define MAX_NB_CLIENTS 3

int		create_server(int port);
void	run_server(Tintin_reporter &reporter, int server_fd, int lock_file_fd);
void	exit_daemon(Tintin_reporter &reporter, int server_fd, int lock_file_fd);

#endif