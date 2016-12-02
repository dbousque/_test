

#ifndef FT_P_CLIENT_H
# define FT_P_CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/stat.h>
# include <fcntl.h>

# define READ_BUFF_LEN 32768
# define CMD_RAW_COMMAND 1
# define CMD_CD 2
# define CMD_GET 3
# define CMD_PUT 4
# define RET_ERROR 1
# define RET_SUCCESS 2

typedef struct			s_options
{
	char				*host;
	int					port;
	char				log;
	char				error;
}						t_options;

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

typedef struct			s_response_type
{
	char				type;
	char				*filename;
}						t_response_type;

size_t					ft_strlen(char *str);
void					ft_putstr(char *str);
void					ft_strcat(char *str1, char *str2, size_t from,
																size_t len);
char					ft_strcmp(char *str1, char *str2);
char					*ft_strconcat(char *str1, char *str2, size_t size1,
																size_t size2);
char					char_in_str(char *str, char c);
void					ft_strcpy(char *str1, char *str2, int len);
int						ind_of_char(char *str, char c, int len);
char					get_type_of_command(char *command);
char					is_space(char c);
char					command_is(char *command, char *is);
char					*ft_strdup(char *str);
void					parse_options(int argc, char **argv, t_options *opt);
void					read_response(int server, char type, char *filename);
char					send_command(int server, t_options *options, char *command);
void					handle_get(int server, char *data, int len);

#endif