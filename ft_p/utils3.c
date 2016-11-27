

#include "ft_p_server.h"

void	ft_client_error(t_client_data *client, char *msg)
{
	char	*expl;
	char	*error;
	char	*nl;

	expl = "An error occured : ";
	nl = "\n";
	error = "ERROR";
	ft_putstr(expl);
	ft_putstr(msg);
	ft_putstr(nl);
	write(client->fd, expl, ft_strlen(expl));
	write(client->fd, msg, ft_strlen(msg));
	write(client->fd, nl, ft_strlen(nl));
	write(client->fd, error, ft_strlen(error));
}

void	ft_client_success(t_client_data *client)
{
	char	*success;

	success = "SUCCESS";
	write(client->fd, success, ft_strlen(success));
}