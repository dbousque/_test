

#include "wolf3d.h"

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

int		exit_wolf3d(t_wolf3d *wolf3d)
{
	mlx_destroy_image(wolf3d->window.mlx, wolf3d->window.img);
	mlx_destroy_window(wolf3d->window.mlx, wolf3d->window.win);
	ft_putstr("Goodbye\n");
	exit(0);
	return (0);
}

void	set_color_at(t_wolf3d *wolf3d, int x, int y, int color)
{
	PIXEL_AT(wolf3d->window, x, y) = color;
	if (wolf3d->big_mode)
	{
		PIXEL_AT(wolf3d->window, x + 1, y) = color;
		PIXEL_AT(wolf3d->window, x, y + 1) = color;
		PIXEL_AT(wolf3d->window, x + 1, y + 1) = color;
	}
}

int		millis_since(struct timeval *start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (1000 * (end.tv_sec - start->tv_sec)
		+ (end.tv_usec - start->tv_usec) / 1000);
}

void	ft_itoa(int n, char *res)
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
	ft_itoa(time_taken, ms);
	ft_putstr(ms);
	ft_putstr(" ms");
	ft_putstr(after);
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

/*int		parse_uint(char *str)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	if (!str[0] || str[0] == '0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	draw_line(t_fractol *f, double from[2], double to[2], int iter)
{
	double	x;
	double	y;
	double	step_x;
	double	step_y;
	int		co;

	step_x = fabs(to[0] - from[0]);
	step_y = fabs(to[1] - from[1]);
	x = fmax(step_x, step_y);
	step_x /= x;
	step_y /= x;
	x = from[0];
	y = from[1];
	step_x = to[0] < from[0] ? -step_x : step_x;
	step_y = to[1] < from[1] ? -step_y : step_y;
	co = f->palettes[f->current_palette][iter % PALETTE_LEN];
	co = iter == f->fractals[f->current_fractal].max_iter ? 0 : co;
	while (((step_x >= 0.0 && x <= to[0]) || (step_x < 0.0 && x >= to[0]))
		&& ((step_y >= 0.0 && y <= to[1]) || (step_y < 0.0 && y >= to[1])))
	{
		if (x < f->window.width && y < f->window.height && x >= 0 && y >= 0)
			set_color_at(f, (int)x, (int)y, co);
		x += step_x;
		y += step_y;
	}
}

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}*/
