/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:53:15 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 16:53:18 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*read_tga_error(char *path, char error, int max_size)
{
	if (error == 1)
	{
		ft_putstr("Could not read file \"");
		ft_putstr(path);
		ft_putstr("\"\n");
	}
	if (error == 2)
		ft_putstr("malloc error\n");
	if (error == 3)
	{
		ft_printf("Maximum file size of %d bytes ", max_size);
		ft_printf("exceeded while reading file \"%s\"\n", path);
	}
	return (NULL);
}

char	*flip_rows(char *content, int width, int height, int pixel_width)
{
	char	*res;
	int		x;
	int		y;

	if (!(res = malloc(sizeof(char) * (width * height * pixel_width))))
	{
		ft_putstr("malloc error\n");
		return (NULL);
	}
	content += 18;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width * pixel_width)
		{
			res[(y * width * pixel_width) + x] =
					content[((height - y - 1) * width * pixel_width) + x];
			x++;
		}
		y++;
	}
	free(content - 18);
	return (res);
}

char	*read_tga(char *path, int *width, int *height, int *pixel_width)
{
	char	*content;
	char	error;
	int		max_size;
	int		content_size;

	max_size = 20 * 1024 * 1024;
	content = read_whole_file(path, &error, max_size, &content_size);
	if (error == 1 || error == 2 || error == 3)
		return (read_tga_error(path, error, max_size));
	if (!content)
		return (NULL);
	*width = *((short*)(content + 12));
	*height = *((short*)(content + 14));
	content_size -= 18;
	if (*width * *height * 3 == content_size)
		*pixel_width = 3;
	else if (*width * *height * 4 == content_size)
		*pixel_width = 4;
	else
	{
		ft_putstr("Invalid TGA file\n");
		return (NULL);
	}
	if (!(content = flip_rows(content, *width, *height, *pixel_width)))
		return (NULL);
	return (content);
}
