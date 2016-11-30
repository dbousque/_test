

#ifndef FT_P_SERVER_H
# define FT_P_SERVER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <wordexp.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>

# define NB_CONNECTIONS 100
# define READ_BUFF_LEN 32768
# define CMD_RAW_COMMAND 1
# define CMD_CD 2
# define CMD_GET 3
# define CMD_PUT 4
# define RET_ERROR 1
# define RET_SUCCESS 2

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
	char				*launch_dir;
	char				**env;
}						t_client_data;

typedef struct			s_packet_header
{
	uint8_t				type;
	uint32_t			tot_data_len;
}						t_packet_header;

typedef struct			s_ret_packet_header
{
	uint8_t				status;
	uint32_t			tot_data_len;
}						t_ret_packet_header;

size_t					ft_strlen(char *str);
void					ft_putstr(char *str);
void					ft_error(char *str);
void					log_connection(t_client_data *client);
void					log_closing(t_client_data *client);
char					*ft_strcpy(char *str);
char					*ft_strconcat(char *str1, char *str2, size_t size1,
																size_t size2);
char					*build_file_path(char *dir_path, char *file_name);
char					ft_strcmp(char *str1, char *str2);
void					ft_client_error(t_client_data *client, char *msg);
void					ft_client_success(t_client_data *client, char *msg,
																size_t len);
void					redirect_output(int link[2]);
void					parse_options(int argc, char **argv, t_options *opt);
void					launch_server(int server, t_options *options,
																char **env);
char					*find_executable(char *name, char **env);
void					handle_put(t_client_data *client, t_options *options,
														char *data, int len);
void					interpret_command(t_client_data *client,
						t_options *options, unsigned char *data, int len);
char					execute_command(t_client_data *client,
								t_options *options, wordexp_t *cmd_and_args);
char					complete_command(t_client_data *client,
							unsigned char **data, int *len, uint32_t cmd_len);

#endif