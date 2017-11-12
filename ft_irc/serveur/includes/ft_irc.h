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
# include <sys/time.h>

# define MAX_NB_CONNECTIONS 512
# define USER_BUFFER_SIZE 4096
# define DEFAULT_PORT 4242

# define LOG(mode, ...) \
	do { log_start(mode); printf(__VA_ARGS__); log_end(mode); } while (0)

char	*g_irc_commands[6];
char	g_tmp_buffer[USER_BUFFER_SIZE + 1];

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
	MSG
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

typedef t_parse_message_res t_parse_msg_res;

typedef struct	s_list
{
	void		*elts;
	int			size;
	int			len;
	size_t		elt_size;
}				t_list;

typedef struct	s_circular_buffer
{
	char		data[USER_BUFFER_SIZE];
	int			start;
	int			end;
}				t_circular_buffer;

typedef t_circular_buffer t_circ_buf;

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
	t_circ_buf	read_buffer;
	t_circ_buf	write_buffer;
	int			channels[11];
	char		nickname[10];
	char		ip_name[20];
	int			msg_sent;
	int			command_sent;
	t_mode		mode;
	int			priv_msg_user;
	int			friends[11];
}				t_user;

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
int				ft_strlen(char *str);
char			startswith(char *str, char *start);
char			contains(char *str, int len, char c);
char			ft_streq(char *str1, char *str2);
void			print_parse_message_error(t_parse_message_res res,
																t_user *user);
void			print_msg(t_msg *msg);
void			log_user(t_user *user, char *str);
void			wrong_nb_params(t_user *user, char *command_name,
												int nb_params, int expected);
t_channel		*find_channel(t_env *e, char *channel_name);
t_channel		*find_channel_by_id(t_env *e, int id);
t_channel		*create_channel(t_env *e, char *channel_name,
															char *description);
char			remove_channel_from_user(t_env *e, t_user *user,
														t_channel *channel);
void			remove_channels_from_user(t_env *e, t_user *user);
char			user_in_channel(t_user *user, int channel_id);
void			welcome_user_to_channel(t_user *user, t_channel *channel);
int				parse_port(char *str);
char			init_list(t_list *list, size_t elt_size);
void			*new_elt(t_list *lst);
void			remove_elt(t_list *lst, char *addr);
void			init_circular_buffer(t_circular_buffer *b);
void			circular_buffer_write(t_circular_buffer *b, char *data,
																	int len);
int				circular_buffer_cpy(t_circular_buffer *b, char *dest);
int				circular_buffer_read(t_circular_buffer *b, char *dest);
char			empty(t_circular_buffer *b);
void			init_commands_names(void);
void			init_users(t_user *users);
void			clear_removed_users(t_user *users, int *nb_users);
void			accept_user(int sock_fd, t_user *users, int *nb_users);
void			remove_user(t_env *e, t_user *user);
void			remove_user_ind(t_env *e, int i);
void			read_user_input(t_env *e, int i);
void			write_user_output(t_env *e, int i);
t_parse_msg_res	parse_message(char *msg, int len, t_msg *res);
void			init_msg(t_msg *msg);
void			nick(t_env *e, t_user *user, char **params, int nb_params);
void			join(t_env *e, t_user *user, char **params, int nb_params);
void			leave(t_env *e, t_user *user, char **params, int nb_params);
void			who(t_env *e, t_user *user, char **params, int nb_params);
void			msg(t_env *e, t_user *user, char **params, int nb_params);
char			valid_channel_name(char *str);
char			valid_nickname(char *str);

#endif