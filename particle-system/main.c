/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:11:45 by dbousque          #+#    #+#             */
/*   Updated: 2017/03/02 18:11:46 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myopengl.h"

char		init_shaders(void)
{
	g_obj_program = new_shader_program("shaders/test1.vs", "shaders/test1.fs");
	if (!g_obj_program)
		return (0);
	return (1);
}

int			main2(char **argv, t_window *window, t_list *objs)
{
	t_light				*light;

	if (!load_object_file(argv[1], objs))
	{
		printf("could not load .object file %s\n", argv[1]);
		return (-1);
	}
	main_loop(window, objs);
	return (0);
}

int			main(int argc, char **argv)
{
	t_window			*window;
	t_list				*objs;

	if (argc != 2)
	{
		show_help();
		return (-1);
	}
	setup_keys();
	setup_conf();
	init_camera();
	window = setup_window(g_conf.win_width, g_conf.win_height,
															"scop - dbousque");
	if (!window)
		return (-1);
	glEnable(GL_DEPTH_TEST);
	if (!init_shaders())
		return (-1);
	objs = new_list(sizeof(t_globj*));
	return (main2(argv, window, objs));
}
