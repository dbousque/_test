

#include "fractol.h"

char	ft_streq(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (1);
	return (0);
}

void	maybe_update_current_fractal(t_fractol *fractol, int argc, char **argv)
{
	int		fractal_ind;

	fractal_ind = 0;
	if (argc > 1)
	{
		if (ft_streq(argv[1], "mandelbrot"))
			fractal_ind = 0;
		else if (ft_streq(argv[1], "julia"))
			fractal_ind = 1;
		else if (ft_streq(argv[1], "ship"))
			fractal_ind = 2;
		else
			ft_putstr("Invalid fractal name, defaulting to mandelbrot\n");
	}
	fractol->current_fractal = fractal_ind;
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

void	zoom_on_point(t_fractal *fractal, double x, double y, float quantity,
															t_fractol *fractol)
{
	fractal->zoom *= quantity;
	if (quantity >= 1.0)
	{
		fractal->decal_x += (x - fractal->decal_x) /
				(double)fractol->window.width * (fractol->window.width / 20);
		fractal->decal_y += (y - fractal->decal_y) /
				(double)fractol->window.height * (fractol->window.height / 20);
	}
	else
	{
		fractal->decal_x -= (x - fractal->decal_x) /
				(double)fractol->window.width * (fractol->window.width / 20);
		fractal->decal_y -= (y - fractal->decal_y) /
				(double)fractol->window.height * (fractol->window.height / 20);
	}
}

void	zoom_on_mouse(t_fractal *fractal, float quantity, t_fractol *fractol)
{
	double	actual_x;
	double	actual_y;
	double	pixel_decal_mouse_x;
	double	pixel_decal_mouse_y;

	pixel_decal_mouse_x = (double)fractol->window.mouse.x /
														(double)fractal->zoom;
	pixel_decal_mouse_y = (double)fractol->window.mouse.y /
														(double)fractal->zoom;
	actual_x = fractal->decal_x + pixel_decal_mouse_x;
	actual_y = fractal->decal_y + pixel_decal_mouse_y;
	zoom_on_point(fractal, actual_x, actual_y, quantity, fractol);
}
