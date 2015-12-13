

#include "fdf.h"

int		ft_get_color(t_point *p1, t_point *p2, double percentage)
{
	double	height;
	int		green;

	height = p1->height + ((p2->height - p1->height) * percentage / 100.0);
	green = 0x0000CC - height * 10;
	return (0xCC00CC + green * 256);
}

int		rgb_to_color(unsigned char r, unsigned char g, unsigned int b)
{
	return (r * 256 * 256 + g * 256 + b);
}

int		ft_get_color2(t_point *p1, t_point *p2, double percentage)
{
	double	height;
	int		res;

	height = p1->height + ((p2->height - p1->height) * percentage / 100.0);
	res = rgb_to_color(50 + height * 20, 50 + height * 20, 50 + height * 20);
	return (res);
}

int		ft_get_color3(t_point *p1, t_point *p2, double percentage)
{
	double	height;
	int		green;

	height = p1->height + ((p2->height - p1->height) * percentage / 100.0);
	green = 0x0000CC - height * 10;
	return (0xCC00CC + green * 256);
}
