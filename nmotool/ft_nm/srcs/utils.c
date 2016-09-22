/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 17:59:09 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/22 18:00:39 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstrnl(char *str)
{
	ft_putstr(str);
	write(1, "\n", 1);
}

void	print_error(char *str)
{
	ft_putstr("\033[91m");
	ft_putstr("[ERROR] ");
	ft_putstr("\033[0m");
	ft_putstrnl(str);
}

void	print_error_file(char *str, char *filename)
{
	ft_putstr("\033[91m");
	ft_putstr("[ERROR] ");
	ft_putstr("\033[0m");
	ft_putstr(filename);
	ft_putstr(" : ");
	ft_putstrnl(str);
}

void	print_format(void)
{
	char	*t;

	t = "Bad format. Expected \"ft_nm <filename1> [<filename2] [...]\"";
	print_error(t);
}
