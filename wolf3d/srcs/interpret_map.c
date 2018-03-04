

#include "wolf3d.h"

char	interpret_err(t_wolf3d *wolf3d, char *msg)
{
	free_map(&(wolf3d->map));
	ft_putstr(msg);
	return (0);
}

t_block	*find_block(t_wolf3d *wolf3d, int id)
{
	t_block	*tmp_block;
	int		i;

	i = 0;
	while (i < wolf3d->map.blocks.len)
	{
		tmp_block = &(((t_block*)wolf3d->map.blocks.elts)[i]);
		if (tmp_block->id == id)
			return (tmp_block);
		i++;
	}
	ft_putstr("a block refered to by id does not exist\n");
	return (NULL);
}

void	set_seen_player(t_wolf3d *wolf3d, int i, char *seen_player)
{
	wolf3d->player.x = i + 0.5;
	*seen_player = 1;
}

char	interpret_map_row(t_wolf3d *wolf3d, t_value *tmp_tab, int *width,
															char *seen_player)
{
	int		i;
	int		id;
	t_block	**block;

	i = 0;
	while (get_tab(tmp_tab)[i])
	{
		if (get_tab(tmp_tab)[i]->type != LONG)
			return (interpret_err(wolf3d, "a map element isn't an integer\n"));
		if (!(block = new_elt(&(wolf3d->map.blocks_positions))))
			return (interpret_err(wolf3d, "malloc error\n"));
		id = *((int*)get_tab(tmp_tab)[i]->data);
		if (id == 1 && *seen_player)
			return (interpret_err(wolf3d, "player must appear only once\n"));
		*block = NULL;
		if (id == 1)
			set_seen_player(wolf3d, i, seen_player);
		else if (id != 0 && !(*block = find_block(wolf3d, id)))
			return (interpret_err(wolf3d, ""));
		i++;
	}
	if (i == 0 || (*width != 0 && i != *width))
		return (interpret_err(wolf3d, "rows must have = n of elts and > 0\n"));
	if (*width == 0)
		*width = i;
	return (i);
}

char	interpret_map(t_wolf3d *wolf3d, t_value *map)
{
	t_value		*tmp_tab;
	int			i;
	int			width;
	char		seen_player;
	char		old_seen_player;

	seen_player = 0;
	width = 0;
	i = 0;
	while ((tmp_tab = get_tab(map)[i]))
	{
		if (tmp_tab->type != ARRAY)
			return (interpret_err(wolf3d, "one map row is not an array\n"));
		old_seen_player = seen_player;
		if (!(interpret_map_row(wolf3d, tmp_tab, &width, &seen_player)))
			return (0);
		if (old_seen_player != seen_player)
			wolf3d->player.y = i + 0.5;
		i++;
	}
	if (i == 0)
		return (interpret_err(wolf3d, "map must have at least one block\n"));
	if (!seen_player)
		return (interpret_err(wolf3d, "the player must be placed on map\n"));
	wolf3d->map.width = width;
	wolf3d->map.height = i;
	return (1);
}

char	interpret_map_file(t_wolf3d *wolf3d, t_value *map_json)
{
	t_value		*json;

	ft_putstr("Reading map file...\n");
	if (map_json->type != DICT)
		return (interpret_err(wolf3d, "File is not a JSON object\n"));
	if (!(json = get_val(map_json, "textures")))
		return (interpret_err(wolf3d, "Missing \"textures\" field\n"));
	if (json->type != ARRAY)
		return (interpret_err(wolf3d, "\"textures\" field is not an array\n"));
	if (!interpret_textures(wolf3d, json))
		return (0);
	if (!(json = get_val(map_json, "blocks")))
		return (interpret_err(wolf3d, "Missing \"blocks\" field\n"));
	if (json->type != ARRAY)
		return (interpret_err(wolf3d, "\"blocks\" field is not an array\n"));
	if (!interpret_blocks(wolf3d, json))
		return (0);
	if (!(json = get_val(map_json, "map")))
		return (interpret_err(wolf3d, "Missing \"map\" field\n"));
	if (json->type != ARRAY)
		return (interpret_err(wolf3d, "\"map\" field is not an array\n"));
	if (!interpret_map(wolf3d, json))
		return (0);
	ft_putstr("done\n");
	return (1);
}