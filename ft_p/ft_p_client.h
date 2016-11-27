

#ifndef FT_P_CLIENT_H
# define FT_P_CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>

# define CMD_RAW_COMMAND 1
# define CMD_CD 2
# define CMD_GET 3
# define CMD_PUT 4

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
	uint64_t			tot_data_len;
}						t_packet_header;

size_t					ft_strlen(char *str);
void					ft_putstr(char *str);
void					ft_strcat(char *str1, char *str2, size_t from,
																size_t len);
char					ft_strcmp(char *str1, char *str2);
char					*ft_strconcat(char *str1, char *str2, size_t size1,
																size_t size2);
char					char_in_str(char *str, char c);
void					parse_options(int argc, char **argv, t_options *opt);

#endif