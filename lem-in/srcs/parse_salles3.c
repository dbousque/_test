/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_salles3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 16:34:37 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/08 16:35:11 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		strstrlen(char **strstr)
{
	int		i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}

char	only_numbers(char *str)
{
	int		i;

	if (*str == '-')
		str++;
	if (ft_strlen(str) < 1)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char	free_parts_n_return(char **parts, char return_value)
{
	int		i;
	int		len;

	i = 0;
	len = strstrlen(parts);
	while (i < len)
	{
		free(parts[i]);
		parts[i] = NULL;
		i++;
	}
	free(parts);
	parts = NULL;
	return (return_value);
}

char	is_input_correct(char *line)
{
	char	**parts;

	if (line[0] == '#')
		return (1);
	if (line[0] == 'L')
		return (0);
	if (ft_strlen(line) < 5)
		return (0);
	if (!(parts = ft_strsplit(line, ' ')))
		return (-1);
	if (strstrlen(parts) != 3 || !only_numbers(parts[1])
		|| !only_numbers(parts[2]))
		return (free_parts_n_return(parts, 0));
	return (free_parts_n_return(parts, 1));
}

char	is_start_or_end_salle(char **line, t_salle **start_salle,
									t_salle **end_salle, t_list **lines_end)
{
	char	start_end;

	start_end = 0;
	if ((*line)[0] == '#')
	{
		if ((*line)[1] != '#')
			return (-2);
		if ((*line)[2] && ft_strcmp(*line + 2, "start") == 0)
			start_end = 1;
		else if ((*line)[2] && ft_strcmp(*line + 2, "end") == 0)
			start_end = 2;
		else
			return (-2);
		if ((*start_salle && start_end == 1) || (*end_salle && start_end == 2))
			return (-1);
		ft_lstaddend(lines_end,
					ft_lstnew(*line, sizeof(char) * (ft_strlen(*line) + 1)));
		free(*line);
		if (get_next_line(0, line) == -1)
			return (-1);
		if (is_input_correct(*line) != 1 || !(*line) || ft_strlen(*line) <= 0)
			return (-1);
	}
	return (start_end);
}
