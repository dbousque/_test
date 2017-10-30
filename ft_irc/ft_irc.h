#ifndef FT_IRC_H
# define FT_IRC_H

# include <stdio.h>

char  *g_irc_commands[] =
{
	"/nick",
	"/join",
	"/leave",
	"/who",
	"/msg",
	"/connect",
	0
};

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

typedef struct	s_user t_user;

typedef struct	s_user
{
	int			id;
	int			fd;
	int			channels[10];
	char		nickname[9];
	char		*address;
	int			msg_sent;
	int			command_sent;
	t_mode		mode;
	int			priv_msg_user;
	int			friends[10];
}				t_user;

#endif