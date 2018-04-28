/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_blocks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:52:09 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 16:52:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_texture	*find_texture(t_wolf3d *wolf3d, t_value *texture_name)
{
	char		*name;
	int			i;
	t_texture	*tmp_texture;

	name = texture_name->data;
	i = 0;
	while (i < wolf3d->map.textures.len)
	{
		tmp_texture = &(((t_texture*)wolf3d->map.textures.elts)[i]);
		if (equal_strings(tmp_texture->name, name))
			return (tmp_texture);
		i++;
	}
	ft_putstr("a name does not reference any valid texture\n");
	return (NULL);
}

char	populate_block(t_wolf3d *wolf3d, t_value *j_b, t_block *block)
{
	t_value		*faces;

	block->id = *((int*)(get_val(j_b, "id")->data));
	block->go_through = *((char*)(get_val(j_b, "go_through")->data));
	block->is_object = get_val(j_b, "obj_texture") ? 1 : 0;
	if (block->is_object)
	{
		block->obj_texture = find_texture(wolf3d, get_val(j_b, "obj_texture"));
		if (!block->obj_texture)
			return (0);
	}
	else
	{
		faces = get_val(j_b, "faces");
		block->faces[0] = find_texture(wolf3d, get_tab(faces)[0]);
		block->faces[1] = find_texture(wolf3d, get_tab(faces)[1]);
		block->faces[2] = find_texture(wolf3d, get_tab(faces)[2]);
		block->faces[3] = find_texture(wolf3d, get_tab(faces)[3]);
		if (!block->faces[0] || !block->faces[1] ||
			!block->faces[2] || !block->faces[3])
		{
			return (0);
		}
	}
	return (1);
}

char	unique_block_id(t_list2 *blocks, int id)
{
	char		seen_once;
	t_block		*tmp_block;
	int			i;

	seen_once = 0;
	i = 0;
	while (i < blocks->len)
	{
		tmp_block = &(((t_block*)blocks->elts)[i]);
		if (tmp_block->id == id)
		{
			if (seen_once)
				return (0);
			seen_once = 1;
		}
		i++;
	}
	return (1);
}

char	interpret_blocks(t_wolf3d *wolf3d, t_value *blocks)
{
	t_block		*tmp_block;
	int			i;
	char		*error_msg;

	i = 0;
	while (get_tab(blocks)[i])
	{
		if (!valid_block(get_tab(blocks)[i], &error_msg))
			return (interpret_err(wolf3d, error_msg));
		if (!(tmp_block = new_elt(&(wolf3d->map.blocks))))
			return (interpret_err(wolf3d, "malloc error\n"));
		if (!populate_block(wolf3d, get_tab(blocks)[i], tmp_block))
			return (interpret_err(wolf3d, ""));
		if (tmp_block->id < 2)
			return (interpret_err(wolf3d, "a block id < 2\n"));
		if (!unique_block_id(&(wolf3d->map.blocks), tmp_block->id))
			return (interpret_err(wolf3d, "a block id appears twice\n"));
		i++;
	}
	return (1);
}
