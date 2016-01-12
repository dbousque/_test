

#include "ft_ls.h"

int		next_tab(int largest)
{
	return (largest + 8 - largest % 8);
}

int		get_largest_string(char **strings)
{
	int		i;
	int		largest;

	i = 0;
	largest = -1;
	while (strings[i])
	{
		if ((int)ft_strlen(strings[i]) > largest)
			largest = (int)ft_strlen(strings[i]);
		i++;
	}
	return (next_tab(largest));
}

void	print_n_tabs(int n)
{
	while (n > 0)
	{
		ft_putstr("\t");
		n--;

	}
}

int		print_string_array_columns(char **strings, int nb)
{
	int				i;
	int				x;
	int				largest;
	int				nb_per_line;
	int				nb_lines;
	struct winsize	*w;

	largest = get_largest_string(strings);
	if (!(w = (struct winsize*)malloc(sizeof(struct winsize))))
		return (0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, w);
	nb_per_line = w->ws_col / largest;
	nb_lines = nb / nb_per_line + 1;
	x = 0;
	while (x < nb_lines && x < nb)
	{
		i = 0;
		while (i < nb_per_line && i * nb_lines + x < nb)
		{
			ft_putstr(strings[i * nb_lines + x]);
			if (i + 1 < nb_per_line && (i + 1) * nb_lines + x < nb)
				print_n_tabs((largest - ft_strlen(strings[i * nb_lines + x]) + 7) / 8);
			i++;
		}
		ft_putchar('\n');
		x++;
	}
	return (1);
}
