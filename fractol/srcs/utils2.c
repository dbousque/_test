

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
