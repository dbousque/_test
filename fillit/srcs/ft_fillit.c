/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:14:50 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/03 16:31:53 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_exit(char *file_content, t_tetrimino **tetris)
{
	if (tetris)
		ft_del_tetris(tetris);
	if (file_content)
		ft_strdel(&file_content);
	ft_putendl("error");
	return (0);
}

int			main(int argc, char **argv)
{
	char			*file_content;
	char			**solution;
	t_tetrimino		**tetris;

	tetris = NULL;
	if (argc == 2)
	{
		if (!(file_content = ft_read_file(argv[1])))
			return (ft_exit(file_content, tetris));
		if (!ft_valid_file(file_content))
			return (ft_exit(file_content, tetris));
		tetris = ft_get_tetriminos(file_content);
		if (tetris == NULL)
			return (ft_exit(file_content, tetris));
		solution = ft_solve_tetris(tetris);
		if (!solution)
			return (ft_exit(file_content, tetris));
		ft_putstrstr(solution);
	}
	return (0);
}
