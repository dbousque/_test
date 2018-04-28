/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_fractol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 14:47:41 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 14:47:43 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_color_at(t_fractol *fractol, int x, int y, int color)
{
	PIXEL_AT(fractol->window, x, y) = color;
	if (fractol->big_mode)
	{
		PIXEL_AT(fractol->window, x + 1, y) = color;
		PIXEL_AT(fractol->window, x, y + 1) = color;
		PIXEL_AT(fractol->window, x + 1, y + 1) = color;
	}
}

void	*compute_part(void *param)
{
	int				xy[2];
	int				it;
	int				co;
	t_thread_data	*d;
	t_fractal		*fr;

	d = (t_thread_data*)param;
	fr = &(d->f->fractals[d->f->current_fractal]);
	xy[1] = d->from_y;
	while (xy[1] < d->until_y)
	{
		xy[0] = d->from_x;
		while (xy[0] < d->until_x)
		{
			it = fr->handle(fr, xy[0] / fr->zoom + fr->decal_x,
				xy[1] / fr->zoom + fr->decal_y, &(d->f->window));
			co = d->f->palettes[d->f->current_palette][it % PALETTE_LEN];
			co = it == d->f->fractals[d->f->current_fractal].max_iter ? 0 : co;
			set_color_at(d->f, xy[0], xy[1], co);
			xy[0] += 1 + d->f->big_mode;
		}
		xy[1] += 1 + d->f->big_mode;
	}
	return (NULL);
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

void	launch_thread(pthread_t *threads, t_thread_data *data, int i)
{
	if (pthread_create(&(threads[i]), NULL, compute_part, &(data[i])) != 0)
	{
		ft_putstr("Error while creating thread\n");
		exit(1);
	}
}

void	compute_fractol(t_fractol *fractol)
{
	struct timeval	start;
	t_thread_data	data[NB_THREADS];
	pthread_t		threads[NB_THREADS];
	int				i;

	gettimeofday(&start, NULL);
	if (fractol->fractals[fractol->current_fractal].raw)
		fractol->fractals[fractol->current_fractal].raw_handle(fractol);
	else
	{
		i = 0;
		while (i < NB_THREADS)
		{
			data[i].f = fractol;
			data[i].from_x = fractol->window.width / NB_THREADS * i;
			data[i].until_x = fractol->window.width / NB_THREADS * (i + 1);
			data[i].from_y = 0;
			data[i].until_y = fractol->window.height;
			launch_thread(threads, data, i);
			i++;
		}
		wait_for_threads_to_finish(threads);
	}
	print_time_taken(&start, "Computing took ", "\n");
}
