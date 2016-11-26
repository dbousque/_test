

#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define NB_CONNECTIONS 100
# define READ_BUFF_LEN 32768

typedef struct			s_options
{
	int					port;
	char				log;
	char				error;
}						t_options;

typedef struct			s_client_data
{
	int					fd;
	struct sockaddr_in	sockaddr;
	unsigned int		len;
	char				*ip_name;
}						t_client_data;

size_t					ft_strlen(char *str);
void					ft_putstr(char *str);
void					ft_error(char *str);
void					log_connection(t_client_data *client);
void					log_closing(t_client_data *client);
char					*ft_strcpy(char *str);
void					parse_options(int argc, char **argv, t_options *opt);
void					launch_server(int server, t_options *options);

#endif