#ifndef IRC_CLIENT_H
# define IRC_CLIENT_H

# include <stdio.h>
# include <stdlib.h>
# include <netdb.h>
# include <netinet/in.h>
# include <string.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

# define SERVER_DEFAULT_PORT 4242
# define READ_BUFFER_SIZE 4096

typedef struct	s_opts
{
	char		*host;
	int			port;
}				t_opts;

typedef struct	s_env
{
	char		connected;
	int			server_fd;
	fd_set		read_fds;
}				t_env;

void			init_env(t_env *e);
char			parse_options(t_opts *opts, int argc, char **argv);

#endif