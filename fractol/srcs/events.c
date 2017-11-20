

#include "fractol.h"

int		expose_hook(void *param)
{
	t_window	*window;

	window = (t_window*)param;
	render_window(window);
	return (0);
}

int		key_hook(int keycode, void *param)
{
	t_window	*window;

	window = (t_window*)param;
	if (IS_ESC(keycode))
		return (exit_fractol(window));
	render_window(window);
	return (0);
}

int		mouse_hook(int keycode, int x, int y, void *param)
{
	t_window	*window;

	(void)keycode;
	(void)x;
	(void)y;
	window = (t_window*)param;
	render_window(window);
	return (0);
}