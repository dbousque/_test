/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:06:26 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/18 18:06:29 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

size_t			ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void			millis_sleep(unsigned int millis)
{
	struct timespec	time;
	struct timespec	ignore;
	unsigned int	seconds;
	long			nanos;

	seconds = millis / 1000;
	nanos = (millis - (seconds * 1000)) * 1000000;
	time.tv_sec = seconds;
	time.tv_nsec = nanos;
	nanosleep(&time, &ignore);
}
