

#include "wolf3d.h"

int		expose_hook(void *param)
{
	t_wolf3d	*wolf3d;

	wolf3d = (t_wolf3d*)param;
	wolf3d->changed = 1;
	return (0);
}

int		key_pressed_hook(int keycode, void *param)
{
	t_wolf3d	*wolf3d;

	wolf3d = (t_wolf3d*)param;
	if (IS_ESC(keycode))
		return (exit_wolf3d(wolf3d));
	if (IS_B(keycode))
		wolf3d->big_mode = wolf3d->big_mode ? 0 : 1;
	return (0);
}

int		key_released_hook(int keycode, void *param)
{
	t_wolf3d	*wolf3d;

	wolf3d = (t_wolf3d*)param;
	(void)wolf3d;
	(void)keycode;
	return (0);
}

int		mouse_move_hook(int x, int y, void *param)
{
	t_wolf3d	*wolf3d;

	wolf3d = (t_wolf3d*)param;
	wolf3d->changed = 1;
	wolf3d->window.mouse.x = x;
	wolf3d->window.mouse.y = y;
	return (0);
}

int		mouse_hook(int keycode, int x, int y, void *param)
{
	t_wolf3d	*wolf3d;

	(void)keycode;
	wolf3d = (t_wolf3d*)param;
	wolf3d->changed = 1;
	wolf3d->window.mouse.x = x;
	wolf3d->window.mouse.y = y;
	return (0);
}
