

#include "fdf.h"

int		ft_unexpected_error(void)
{
	ft_putendl("unexpected error");
	return (1);
}

int		ft_map_error(void)
{
	ft_putendl("map error");
	return (1);
}

int		ft_connection_failed(void)
{
	ft_putendl("connection to X server failed");
	return (1);
}
