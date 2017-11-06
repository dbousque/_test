#ifndef FT_IRC_H
# define FT_IRC_H

# include <stdio.h>
# include <stdlib.h>
# include <netdb.h>
# include <netinet/in.h>
# include <string.h>
# include <sys/select.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <time.h>

# define MAX_NB_CONNECTIONS 512
# define USER_BUFFER_SIZE 4096
# define DEFAULT_PORT 4242

# define LOG(mode, ...) log_start(mode); printf(__VA_ARGS__); log_end(mode);

char	*g_irc_commands[7];

typedef enum
{
	INFO,
	DEBUG,
	ERROR
} t_log_mode;

typedef enum
{
	NICK,
	JOIN,
	LEAVE,
	WHO,
	MSG,
	CONNECT
} t_command;

typedef enum
{
	OK,
	NO_COMMAND,
	MISSING_CL_LF,
	TOO_LONG,
	CONTAINS_NUL,
	FORBIDDEN_CHARACTER,
	TOO_MANY_PARAMS
} t_parse_message_res;

typedef struct	s_msg
{
	t_command	command;
	char		*params[16];
}				t_msg;

typedef struct	s_channel
{
	int			id;
	char		name[200];
	char		description[300];
}				t_channel;

typedef enum
{
	STD,
	PRIV_MSG
} t_mode;

typedef struct	s_user
{
	char		free;
	int			id;
	int			fd;
	char		write_buffer[USER_BUFFER_SIZE];
	char		read_buffer[513];
	int			nb_in_write_buffer;
	int			nb_in_read_buffer;
	int			channels[10];
	char		nickname[10];
	char		ip_name[20];
	int			msg_sent;
	int			command_sent;
	t_mode		mode;
	int			priv_msg_user;
	int			friends[11];
}				t_user;

typedef struct	s_list
{
	void		*elts;
	int			size;
	int			len;
	size_t		elt_size;
}				t_list;

typedef struct	s_env
{
	int			sock_fd;
	t_user		users[MAX_NB_CONNECTIONS];
	t_list		channels;
	int			nb_users;
	fd_set		read_fds;
	fd_set		write_fds;
}				t_env;

void			log_start(t_log_mode mode);
void			log_end(t_log_mode mode);
char			init_list(t_list *list, size_t elt_size);
void			*new_elt(t_list *lst);
void			init_commands_names(void);
void			init_users(t_user *users);
void			clear_removed_users(t_user *users, int *nb_users);
void			accept_user(int sock_fd, t_user *users, int *nb_users);
void			remove_user(t_user *users, int i, int nb_users);

#endif