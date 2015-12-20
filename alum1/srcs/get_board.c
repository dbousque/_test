/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 22:07:47 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/20 12:44:27 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alum1.h"

int		ft_strstrlen(char **strstr)
{
	int		i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

char	valid_line(char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(line) <= 0 || ft_strlen(line) > 5)
		return (0);
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int		check_and_assign(char **file_cont, int **board, int i)
{
	if (!file_cont[i + 1] && (file_cont[i][0] || i == 0))
		return (-1);
	if (!file_cont[i][0])
	{
		if (file_cont[i + 1])
			return (-1);
	}
	else
	{
		if (!(valid_line(file_cont[i])))
			return (-1);
		if (((*board)[i] = ft_atoi(file_cont[i])) < 1 || (*board)[i] > 10000)
			return (-1);
	}
	return (0);
}

int		get_board(char **file_cont, int **board, int *len)
{
	int		i;
	int		length;

	i = 0;
	length = ft_strstrlen(file_cont);
	if (!(*board = (int*)malloc(sizeof(int) * (length))))
		return (-2);
	board[length - 1] = NULL;
	*len = length - 1;
	while (file_cont[i])
	{
		if (check_and_assign(file_cont, board, i) == -1)
			return (-1);
		i++;
	}
	if (i < 1)
		return (-1);
	return (0);
}
