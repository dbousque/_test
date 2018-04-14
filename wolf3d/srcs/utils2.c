

#include "wolf3d.h"

void	render_wolf3d(t_wolf3d *wolf3d)
{
	apply_image_to_window(&(wolf3d->window));
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

float	make_distance(int i, int block_until)
{
	float	part1;
	float	part2;

	part1 = (float)i / (block_until * 2);
	part2 = 1.015 - ((float)i / (block_until * 2));
	return (fminf(part1, part2));
}