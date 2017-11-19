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
# include <ncurses.h>

# define SERVER_DEFAULT_PORT 4242
# define READ_BUFFER_SIZE 4096

char	*g_irc_commands[2];
char	g_priv_user[30];
char	g_priv_user_mode;

typedef enum
{
	CONNECT
}	t_command;

typedef enum
{
	COMMAND_OK,
	NO_COMMAND,
	MISSING_CL_LF,
	TOO_LONG,
	CONTAINS_NUL,
	FORBIDDEN_CHARACTER,
	TOO_MANY_PARAMS
}	t_parse_message_res;

typedef t_parse_message_res	t_parse_msg_res;

typedef WINDOW	t_window;

typedef struct timeval	t_time;

typedef struct	s_windows
{
	t_window	*users_win;
	t_window	*input_win;
	t_window	*text_win;
	t_window	*info_win;
}				t_windows;

t_windows		g_windows;

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
	t_time		last_users_update;
	t_time		last_nick_update;
	t_time		last_privuser_update;
}				t_env;

typedef struct	s_msg
{
	t_command	command;
	char		*params[16];
}				t_msg;

void			init_env(t_env *e);
char			parse_options(t_opts *opts, int argc, char **argv);
char			startswith(char *str, char *start);
int				ft_strlen(char *str);
char			contains(char *str, int len, char c);
char			ft_streq(char *str1, char *str2);
void			update_nick_info(char *nick);
int				parse_port(char *str);
void			init_msg(t_msg *msg);
void			init_windows(void);
void			close_windows(void);
void			wwrite(t_window *window, char *str);
void			win_write(char *str);
void			win_input_write(char *str);
t_parse_msg_res	parse_message(char *msg, int len, t_msg *res);
void			init_commands_names(void);

#endif
