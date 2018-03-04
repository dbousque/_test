

#include "wolf3d.h"

char	valid_texture(t_value *texture, char **error_msg)
{
	if (texture->type != DICT)
	{
		*error_msg = "a texture is not an object\n";
		return (0);
	}
	if (!get_val(texture, "name"))
	{
		*error_msg = "a texture does not have a name\n";
		return (0);
	}
	if (!get_val(texture, "file"))
	{
		*error_msg = "a texture does not have a file\n";
		return (0);
	}
	if (get_val(texture, "name")->type != STRING)
	{
		*error_msg = "a texture's name is not a string\n";
		return (0);
	}
	if (get_val(texture, "file")->type != STRING)
	{
		*error_msg = "a texture's file is not a string\n";
		return (0);
	}
	return (1);
}

int		*read_image_file(char *path, int *width, int *height, char **to_free)
{
	int		*pixels;

	//if (endswith(img_path, ".tga"))
		pixels = (int*)read_tga(path, width, height);
		if (!pixels)
			return (NULL);
		*to_free = ((char*)pixels) - 18;
		return (pixels);
	//return (SOIL_load_image(path, width, height, &channels, SOIL_LOAD_RGB));
}

char	populate_texture(t_value *json_texture, t_texture *texture)
{
	char	*path;
	int		width;
	int		height;
	int		*pixels;

	texture->name = NULL;
	texture->pixels = NULL;
	texture->to_free = NULL;
	path = get_val(json_texture, "file")->data;
	pixels = read_image_file(path, &width, &height, &(texture->to_free));
	if (!pixels)
		return (0);
	texture->name = copy_str(get_val(json_texture, "name")->data);
	texture->pixels = pixels;
	texture->width = width;
	texture->height = height;
	return (1);
}

char	unique_texture_name(t_list2 *textures, char *name)
{
	char		seen_once;
	t_texture	*tmp_texture;
	int			i;

	seen_once = 0;
	i = 0;
	while (i < textures->len)
	{
		tmp_texture = &(((t_texture*)textures->elts)[i]);
		if (equal_strings(tmp_texture->name, name))
		{
			if (seen_once)
				return (0);
			seen_once = 1;
		}
		i++;
	}
	return (1);
}

char	interpret_textures(t_wolf3d *wolf3d, t_value *textures)
{
	t_texture	*tmp_texture;
	int			i;
	char		*error_msg;

	i = 0;
	while (get_tab(textures)[i])
	{
		if (!valid_texture(get_tab(textures)[i], &error_msg))
			return (interpret_err(wolf3d, error_msg));
		if (!(tmp_texture = new_elt(&(wolf3d->map.textures))))
			return (interpret_err(wolf3d, "malloc error\n"));
		if (!populate_texture(get_tab(textures)[i], tmp_texture))
			return (interpret_err(wolf3d, ""));
		if (!unique_texture_name(&(wolf3d->map.textures), tmp_texture->name))
			return (interpret_err(wolf3d, "a texture name appears twice\n"));
		i++;
	}
	return (1);
}