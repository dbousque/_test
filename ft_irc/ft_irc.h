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

char  *g_irc_commands[7];

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
	char 		free;
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

char			init_list(t_list *list, size_t elt_size);
void			*new_elt(t_list *lst);

#endif