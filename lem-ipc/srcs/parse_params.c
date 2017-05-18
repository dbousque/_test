/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:05:46 by dbousque          #+#    #+#             */
/*   Updated: 2017/05/18 18:05:49 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_ipc.h"

unsigned int	parse_uint_error(char *msg, char *error)
{
	*error = 1;
	write(1, msg, ft_strlen(msg));
	return (0);
}

unsigned int	parse_uint(char *str, char *error)
{
	unsigned long	res;
	int				i;

	i = 0;
	res = 0;
	if (str[0] == '0')
	{
		if (ft_strlen(str) == 1)
			return (0);
		return (parse_uint_error("number starts with 0\n", error));
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > UINT_MAX)
		{
			return (parse_uint_error("number is higher than UINT_MAX\n",
																	error));
		}
		i++;
	}
	if (str[i] != '\0')
		return (parse_uint_error("invalid number\n", error));
	return ((unsigned int)res);
}

char			set_params(char error, unsigned int tmp, char **argv,
															t_params *params)
{
	tmp = parse_uint(argv[1], &error);
	if (error)
		return (0);
	params->team_id = tmp;
	tmp = parse_uint(argv[2], &error);
	if (error)
		return (0);
	params->move_sleep_millis = tmp;
	tmp = parse_uint(argv[3], &error);
	if (error)
		return (0);
	params->initial_sleep = tmp;
	return (1);
}

char			parse_er(char *msg)
{
	printf("%s\n", msg);
	return (0);
}

char			parse_params(int argc, char **argv, t_params *params)
{
	char			error;
	unsigned int	tmp;

	if (argc < 4 || argc > 5)
	{
		printf("format : ./lemipc <team_id:uint> <move_sleep_millis:unint>");
		return (parse_er(" <initial_sleep:unint> ?<board_size:uint>"));
	}
	error = 0;
	tmp = 0;
	if (!(set_params(error, tmp, argv, params)))
		return (0);
	params->board_size = DEFAULT_BOARD_SIZE;
	if (argc == 5)
	{
		tmp = parse_uint(argv[4], &error);
		if (error)
			return (0);
		if (tmp < 2 || tmp > 100)
			return (parse_er("board_size too big or too small, expect 2-100"));
		params->board_size = tmp;
	}
	return (1);
}
