/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:40:07 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:40:09 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_path(void)
{
	char	*path;
	size_t	size;

	size = 1024;
	while (1)
	{
		if (!(path = (char*)malloc(sizeof(char) * size)))
			malloc_error();
		getcwd(path, size);
		if (path)
			break ;
		free(path);
		size *= 2;
	}
	return (path);
}

char	*get_current_dir(void)
{
	char	*path;
	char	*res;
	size_t	i;

	path = get_current_path();
	i = 0;
	while (path[i])
		i++;
	i--;
	while (i > 0 && path[i - 1] != '/')
		i--;
	res = ft_strdup(path + i);
	free(path);
	return (res);
}

int		getch(void)
{
	struct termios	oldtc;
	struct termios	newtc;
	int				ch;

	tcgetattr(STDIN_FILENO, &oldtc);
	newtc = oldtc;
	newtc.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
	return (ch);
}

char	*double_size(char *line, size_t *size)
{
	char	*new_line;
	size_t	i;

	*size *= 2;
	if (!(new_line = (char*)malloc(sizeof(char) * (*size + 1))))
		malloc_error();
	i = 0;
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

size_t	strstrlen(char **strstr)
{
	size_t	i;

	i = 0;
	while (strstr[i])
		i++;
	return (i);
}
