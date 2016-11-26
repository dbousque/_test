

#include "ft_p_server.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_error(char *str)
{
	ft_putstr("An error occured : ");
	ft_putstr(str);
	ft_putstr("\n");
}

void	log_connection(t_client_data *client)
{
	ft_putstr("Established connection with client ");
	ft_putstr(client->ip_name);
	ft_putstr("\n");
}

void	log_closing(t_client_data *client)
{
	ft_putstr("Closing connection with client ");
	ft_putstr(client->ip_name);
	ft_putstr("\n");
}