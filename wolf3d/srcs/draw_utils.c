

#include "wolf3d.h"

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