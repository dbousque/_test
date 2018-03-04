

#include "wolf3d.h"

void	free_map(t_map *map)
{
	int			i;
	t_texture	*tmp_texture;

	i = 0;
	while (i < map->textures.len)
	{
		tmp_texture = &(((t_texture*)map->textures.elts)[i]);
		if (tmp_texture->name)
			free(tmp_texture->name);
		if (tmp_texture->to_free)
		{
			SOIL_free_image_data
			free(tmp_texture->to_free);
		}
		i++;
	}
	free_list(&(map->textures));
	free_list(&(map->blocks));
	free_list(&(map->blocks_positions));
}

int		exit_wolf3d(t_wolf3d *wolf3d)
{
	mlx_destroy_image(wolf3d->window.mlx, wolf3d->window.img);
	mlx_destroy_window(wolf3d->window.mlx, wolf3d->window.win);
	free_map(&(wolf3d->map));
	ft_putstr("Goodbye\n");
	exit(0);
	return (0);
}

void	set_color_at(t_wolf3d *wolf3d, int x, int y, int color)
{
	PIXEL_AT(wolf3d->window, x, y) = color;
	if (wolf3d->opts.big_mode)
	{
		PIXEL_AT(wolf3d->window, x + 1, y) = color;
		PIXEL_AT(wolf3d->window, x, y + 1) = color;
		PIXEL_AT(wolf3d->window, x + 1, y + 1) = color;
	}
}

void	safe_set_color_at(t_wolf3d *w, int x, int y, int color)
{
	if (x >= 0 && x < w->window.width && y >= 0 && y < w->window.height)
		PIXEL_AT(w->window, x, y) = color;
	if (w->opts.big_mode)
	{
		if (x + 1 >= 0 && x + 1 < w->window.width
			&& y >= 0 && y < w->window.height)
		{
			PIXEL_AT(w->window, x + 1, y) = color;
		}
		if (x >= 0 && x < w->window.width
			&& y + 1 >= 0 && y + 1 < w->window.height)
		{
			PIXEL_AT(w->window, x, y + 1) = color;
		}
		if (x + 1 >= 0 && x + 1 < w->window.width
			&& y + 1 >= 0 && y + 1 < w->window.height)
		{
			PIXEL_AT(w->window, x + 1, y + 1) = color;
		}
	}
}

char	*copy_str(char *str)
{
	char	*res;
	int		i;

	if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	equal_strings(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (str1[i] != str2[i])
		return (0);
	return (1);
}

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

char	endswith(char *str, char *end)
{
	int		len1;
	int		len2;

	len1 = 0;
	while (str[len1])
		len1++;
	len2 = 0;
	while (end[len2])
		len2++;
	while (len1 >= 0 && len2 >= 0)
	{
		if (str[len1] != end[len2])
			return (0);
		len1--;
		len2--;
	}
	if (len2 == -1)
		return (1);
	return (0);
}

void	draw_line(t_wolf3d *w, int from[2], int to[2], int color)
{
	float	x;
	float	y;
	float	step_x;
	float	step_y;

	step_x = fabsf((float)to[0] - (float)from[0]);
	step_y = fabsf((float)to[1] - (float)from[1]);
	x = fmaxf(step_x, step_y);
	step_x /= x;
	step_y /= x;
	x = (float)from[0];
	y = (float)from[1];
	step_x = to[0] < from[0] ? -step_x : step_x;
	step_y = to[1] < from[1] ? -step_y : step_y;
	while (((step_x >= 0.0 && x <= to[0]) || (step_x < 0.0 && x >= to[0]))
		&& ((step_y >= 0.0 && y <= to[1]) || (step_y < 0.0 && y >= to[1])))
	{
		if (x < w->window.width && y < w->window.height && x >= 0 && y >= 0)
			set_color_at(w, (int)x, (int)y, color);
		x += step_x;
		y += step_y;
	}
}

void	safe_draw_line(t_wolf3d *w, int from[2], int to[2], int color)
{
	float	x;
	float	y;
	float	step_x;
	float	step_y;

	step_x = fabsf((float)to[0] - (float)from[0]);
	step_y = fabsf((float)to[1] - (float)from[1]);
	x = fmaxf(step_x, step_y);
	step_x /= x;
	step_y /= x;
	x = (float)from[0];
	y = (float)from[1];
	step_x = to[0] < from[0] ? -step_x : step_x;
	step_y = to[1] < from[1] ? -step_y : step_y;
	while (((step_x >= 0.0 && x <= to[0]) || (step_x < 0.0 && x >= to[0]))
		&& ((step_y >= 0.0 && y <= to[1]) || (step_y < 0.0 && y >= to[1])))
	{
		if (x < w->window.width && y < w->window.height && x >= 0 && y >= 0)
			safe_set_color_at(w, (int)x, (int)y, color);
		x += step_x;
		y += step_y;
	}
}

void	draw_square2(t_wolf3d *w, int from[2], int size, int color)
{
	int		to[2];

	from[1] += size;
	to[0] = from[0] + size;
	to[1] = from[1];
	draw_line(w, from, to, color);
	from[1] -= 1;
	to[1] -= 1;
	draw_line(w, from, to, color);
	from[1] += 1;
	to[1] += 1;
	from[0] += size;
	from[1] -= size;
	draw_line(w, from, to, color);
	from[0] -= 1;
	to[0] -= 1;
	draw_line(w, from, to, color);
}

void	draw_square(t_wolf3d *w, int from[2], int size, int color)
{
	int		to[2];

	to[0] = from[0] + size;
	to[1] = from[1];
	draw_line(w, from, to, color);
	from[1] += 1;
	to[1] += 1;
	draw_line(w, from, to, color);
	from[1] -= 1;
	to[1] -= 1;
	to[0] = from[0];
	to[1] = from[1] + size;
	draw_line(w, from, to, color);
	from[0] += 1;
	to[0] += 1;
	draw_line(w, from, to, color);
	from[0] -= 1;
	to[0] -= 1;
	draw_square2(w, from, size, color);
}

void	clear_screen(t_wolf3d *wolf3d)
{
	int			x;
	int			y;	

	x = 0;
	while (x < wolf3d->window.width)
	{
		y = 0;
		while (y < wolf3d->window.height)
		{
			set_color_at(wolf3d, x, y, 0x000000);
			y++;
		}
		x++;
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
