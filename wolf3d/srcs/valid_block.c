/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:54:08 by dbousque          #+#    #+#             */
/*   Updated: 2018/04/28 16:54:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	valid_block_faces(t_value *block, char **error_msg)
{
	if (!get_tab(get_val(block, "faces"))[0] ||
		!get_tab(get_val(block, "faces"))[1] ||
		!get_tab(get_val(block, "faces"))[2] ||
		!get_tab(get_val(block, "faces"))[3] ||
		get_tab(get_val(block, "faces"))[4])
	{
		*error_msg = "a block's faces is not 4 elements long\n";
		return (0);
	}
	if (get_tab(get_val(block, "faces"))[0]->type != STRING ||
		get_tab(get_val(block, "faces"))[1]->type != STRING ||
		get_tab(get_val(block, "faces"))[2]->type != STRING ||
		get_tab(get_val(block, "faces"))[3]->type != STRING)
	{
		*error_msg = "a block's face is not a string\n";
		return (0);
	}
	return (1);
}

char	valid_block2(t_value *block, char **error_msg)
{
	if (get_val(block, "obj_texture"))
	{
		if (get_val(block, "obj_texture")->type != STRING)
		{
			*error_msg = "a block's obj_texture is not a string\n";
			return (0);
		}
	}
	else
	{
		if (!get_val(block, "faces"))
		{
			*error_msg = "a block is missing a faces or obj_texture field\n";
			return (0);
		}
		if (get_val(block, "faces")->type != ARRAY)
		{
			*error_msg = "a block's faces is not an array\n";
			return (0);
		}
		return (valid_block_faces(block, error_msg));
	}
	return (1);
}

char	valid_block(t_value *block, char **error_msg)
{
	if (block->type != DICT)
	{
		*error_msg = "a block is not an object\n";
		return (0);
	}
	if (!get_val(block, "id"))
	{
		*error_msg = "a block does not have an id\n";
		return (0);
	}
	if (!get_val(block, "go_through"))
	{
		*error_msg = "a block does not have a go_through field\n";
		return (0);
	}
	if (get_val(block, "id")->type != LONG)
	{
		*error_msg = "a block's id is not an integer\n";
		return (0);
	}
	if (get_val(block, "go_through")->type != BOOLEAN)
	{
		*error_msg = "a block's go_through is not a boolean\n";
		return (0);
	}
	return (valid_block2(block, error_msg));
}
