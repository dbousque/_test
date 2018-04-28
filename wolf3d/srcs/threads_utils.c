/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:53:45 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 16:53:47 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		millis_since(struct timeval *start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (1000 * (end.tv_sec - start->tv_sec)
		+ (end.tv_usec - start->tv_usec) / 1000);
}

void	ft_itoa2(int n, char *res)
{
	int		i;
	int		len;
	char	tmp[30];

	i = 0;
	if (n == 0)
	{
		tmp[0] = '0';
		i = 1;
	}
	while (n > 0)
	{
		tmp[i] = '0' + (n % 10);
		i++;
		n /= 10;
	}
	len = i - 1;
	i = 0;
	while (i <= len)
	{
		res[i] = tmp[len - i];
		i++;
	}
	res[i] = '\0';
}

void	print_time_taken(struct timeval *start, char *before, char *after)
{
	char			ms[30];
	int				time_taken;

	ft_putstr(before);
	time_taken = millis_since(start);
	ft_itoa2(time_taken, ms);
	ft_putstr(ms);
	ft_putstr(" ms");
	ft_putstr(after);
}

void	launch_thread(pthread_t *threads, t_thread_data *data, int i)
{
	if (pthread_create(
			&(threads[i]),
			NULL,
			compute_wolf3d_part,
			&(data[i])
		) != 0)
	{
		ft_putstr("Error while creating thread\n");
		exit(1);
	}
}

void	wait_for_threads_to_finish(pthread_t *threads)
{
	int		i;

	i = 0;
	while (i < NB_THREADS)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			ft_putstr("Error while waiting for thread\n");
			exit(1);
		}
		i++;
	}
}
