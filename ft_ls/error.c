/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:39:10 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 16:39:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		unexpected_error(void)
{
	ft_putendl_fd("ft_ls: unexpected error", 2);
	return (0);
}

void	*unexpected_error_null(void)
{
	ft_putendl_fd("ft_ls: unexpected error", 2);
	return (NULL);
}

char	*cut_filename(char *filename)
{
	int		i;

	i = 0;
	while (filename[i])
	{
		if (filename[i] == '/' && filename[i + 1])
		{
			filename += i + 1;
			i = -1;
		}
		i++;
	}
	return (filename);
}

void	print_errno(int error, char *filename)
{
	ft_putstr_fd("ft_ls: ", 2);
	if (filename[0] == '\0')
		ft_putstr_fd("fts_open", 2);
	else
		ft_putstr_fd(cut_filename(filename), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(error), 2);
}
