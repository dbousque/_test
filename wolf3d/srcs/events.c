

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
	if (IS_D(keycode))
		wolf3d->opts.debug_mode = wolf3d->opts.debug_mode ? 0 : 1;
	if (IS_B(keycode))
		wolf3d->opts.big_mode = wolf3d->opts.big_mode ? 0 : 1;
	if (IS_UP(keycode))
		wolf3d->window.pressed_keys[0] = 1;
	if (IS_DOWN(keycode))
		wolf3d->window.pressed_keys[1] = 1;
	if (IS_RIGHT(keycode))
		wolf3d->window.pressed_keys[2] = 1;
	if (IS_LEFT(keycode))
		wolf3d->window.pressed_keys[3] = 1;
	if (IS_A(keycode))
		wolf3d->window.pressed_keys[4] = 1;
	if (IS_S(keycode))
		wolf3d->window.pressed_keys[5] = 1;
	if (IS_Z(keycode))
		wolf3d->window.pressed_keys[6] = 1;
	if (IS_X(keycode))
		wolf3d->window.pressed_keys[7] = 1;
	wolf3d->changed = 1;
	return (0);
}

int		key_released_hook(int keycode, void *param)
{
	t_wolf3d	*wolf3d;

	wolf3d = (t_wolf3d*)param;
	if (IS_UP(keycode))
		wolf3d->window.pressed_keys[0] = 0;
	if (IS_DOWN(keycode))
		wolf3d->window.pressed_keys[1] = 0;
	if (IS_RIGHT(keycode))
		wolf3d->window.pressed_keys[2] = 0;
	if (IS_LEFT(keycode))
		wolf3d->window.pressed_keys[3] = 0;
	if (IS_A(keycode))
		wolf3d->window.pressed_keys[4] = 0;
	if (IS_S(keycode))
		wolf3d->window.pressed_keys[5] = 0;
	if (IS_Z(keycode))
		wolf3d->window.pressed_keys[6] = 0;
	if (IS_X(keycode))
		wolf3d->window.pressed_keys[7] = 0;
	wolf3d->changed = 1;
	return (0);
}

int		mouse_move_hook(int x, int y, void *param)
{
	t_wolf3d	*wolf3d;

	wolf3d = (t_wolf3d*)param;
	wolf3d->window.mouse.x = x;
	wolf3d->window.mouse.y = y;
	wolf3d->changed = 1;
	return (0);
}

int		mouse_hook(int keycode, int x, int y, void *param)
{
	t_wolf3d	*wolf3d;

	(void)keycode;
	wolf3d = (t_wolf3d*)param;
	wolf3d->window.mouse.x = x;
	wolf3d->window.mouse.y = y;
	wolf3d->changed = 1;
	return (0);
}
