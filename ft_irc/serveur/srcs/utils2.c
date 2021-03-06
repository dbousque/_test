/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 17:57:29 by dbousque          #+#    #+#             */
/*   Updated: 2017/12/09 17:57:31 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.h"

void	log_s(t_log_mode mode)
{
	time_t		t;
	struct tm	tm;

	if (mode == INFO)
		printf("\033[1;33m[INFO] ");
	if (mode == DEBUG)
		printf("\033[1;34m[DEBUG]");
	if (mode == ERROR)
		printf("\033[1;31m[ERROR]");
	printf("\033[0m ");
	t = time(NULL);
	tm = *localtime(&t);
	printf("[%d-%02d-%02d %02d:%02d:%02d] ", tm.tm_year + 1900, tm.tm_mon + 1,
								tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	if (mode == INFO)
		printf("\033[1;33m");
	if (mode == DEBUG)
		printf("\033[1;34m");
	if (mode == ERROR)
		printf("\033[1;31m");
}

void	log_e(t_log_mode mode)
{
	(void)mode;
	printf("\033[0m\n");
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	startswith(char *str, char *start)
{
	int		i;

	i = 0;
	while (start[i] && str[i] == start[i])
		i++;
	if (!start[i])
		return (1);
	return (0);
}

char	contains(char *str, int len, char c)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
