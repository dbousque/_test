

#include "corewar.h"

typedef struct		s_instruction
{
	char			*label;
	char			*command;
	int				opcode;
	unsigned char	*params_byte;
	char			**params;
}					t_instruction;

char			is_instruction(char *line)
{
	(void)line;
	return (1);
}

char			is_comment(char *line)
{
	(void)line;
	return (1);
}

unsigned char	get_params_byte(t_instruction *instruct)
{
	unsigned char	res;

	res = 0;
	(void)instruct;
	return (res);
}

int				get_opcode(char *command, int *not_found)
{
	int		i;

	i = 0;
	while (op_tab[i][0])
	{
		if (ft_strcmp(command, op_tab[i][0]) == 0)
		{
			*not_found = 0;
			return (op_tab[i][3]);
		}
		i++;
	}
	return (0);
}

int				get_instruction(char *line, t_instruction *instruct)
{
	int		not_found;

	not_found = 1;
	ft_printf("opcode : %d\n", get_opcode("sti", &not_found));
	return (1);
}

int				get_binary_from_line(char *line, t_list **lines,
															t_list **lines_end)
{
	t_instruction	*instruct;
	char			*ori_line;

	(void)lines;
	(void)lines_end;
	ori_line = line;
	line = ft_strtrim(line);
	free(ori_line);
	if (is_instruction(line))
	{
		if (!(instruct = (t_instruction*)malloc(sizeof(t_instruction))))
			return (0);
		if (!get_instruction(line, instruct))
			return (0);
	}
	else if (!is_comment(line))
		return (0);
	return (1);
}

int				lines_to_res_file(char *filename, t_list *lines)
{
	char	*res_filename;
	int		fd_res;

	if (!(fd_res = create_res_file(filename, &res_filename)))
		return (cant_create_file(res_filename));
	ft_putstr("Writing output program to ");
	ft_putendl(res_filename);
	(void)lines;
	return (0);
}

int				error_while_reading(char *filename)
{
	ft_putstr_fd("Error while reading file ", 2);
	ft_putendl_fd(filename, 2);
	return (0);
}

int				convert_file(char *filename)
{
	char	*line;
	int		ret;
	int		fd;
	t_list	*lines;
	t_list	*lines_end;

	lines_end = NULL;
	lines = NULL;
	fd = open(filename, O_RDONLY);
	if (fd <= -1)
		return (cant_read_file(filename));
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		ft_putendl(line);
		if (!(get_binary_from_line(line, &lines, &lines_end)))
			return (0);
		free(line);
	}
	if (ret == -1)
		return (error_while_reading(filename));
	return (lines_to_res_file(filename, lines));
}
