/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_details2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:09:48 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/12 16:31:29 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		month_to_int(char *month)
{
	if (ft_strcmp(month, "Jan") == 0)
		return (1);
	if (ft_strcmp(month, "Feb") == 0)
		return (2);
	if (ft_strcmp(month, "Mar") == 0)
		return (3);
	if (ft_strcmp(month, "Apr") == 0)
		return (4);
	if (ft_strcmp(month, "Mai") == 0)
		return (5);
	if (ft_strcmp(month, "Jun") == 0)
		return (6);
	if (ft_strcmp(month, "Jul") == 0)
		return (7);
	if (ft_strcmp(month, "Aug") == 0)
		return (8);
	if (ft_strcmp(month, "Sep") == 0)
		return (9);
	if (ft_strcmp(month, "Oct") == 0)
		return (10);
	if (ft_strcmp(month, "Nov") == 0)
		return (11);
	if (ft_strcmp(month, "Dec") == 0)
		return (12);
	return (-1);
}

int		more_or_less_than_six_months(char **date)
{
	char	**current_date;
	int		dat[3];
	int		current_dat[3];
	long	crt;

	crt = time(NULL);
	current_date = ft_strsplit(ctime(&crt), ' ');
	current_dat[0] = ft_atoi(current_date[4]);
	current_dat[1] = month_to_int(current_date[1]);
	current_dat[2] = ft_atoi(current_date[2]);
	dat[0] = ft_atoi(date[4]);
	dat[1] = month_to_int(date[1]);
	dat[2] = ft_atoi(date[2]);
	if (current_dat[0] - dat[0] < -1 || current_dat[0] - dat[0] > 1)
		return (1);
	if (current_dat[0] > dat[0])
		current_dat[1] += 12;
	else if (current_dat[0] < dat[0])
		dat[1] += 12;
	if ((current_dat[1] - dat[1] < -6 || current_dat[1] - dat[1] > 6)
		|| (current_dat[1] - dat[1] == 6 && current_dat[2] - dat[2] >= 0))
		return (1);
	if (current_dat[1] - dat[1] == -6 && current_dat[2] - dat[2] <= 0)
		return (1);
	return (0);
}

void	print_until_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	str[i] = '\0';
	ft_putstr(str);
}

void	print_date(struct stat *file_stats)
{
	char	**date;
	char	**hour;

	date = ft_strsplit(ctime(&file_stats->st_mtimespec.tv_sec), ' ');
	ft_putchar(' ');
	ft_putstr(date[1]);
	ft_putchar(' ');
	if (ft_strlen(date[2]) == 1)
		ft_putchar(' ');
	ft_putstr(date[2]);
	if (more_or_less_than_six_months(date))
	{
		ft_putstr("  ");
		print_until_newline(date[4]);
	}
	else
	{
		hour = ft_strsplit(date[3], ':');
		ft_putchar(' ');
		ft_putstr(hour[0]);
		ft_putchar(':');
		ft_putstr(hour[1]);
	}
}
