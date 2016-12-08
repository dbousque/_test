/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_command2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 16:25:32 by dbousque          #+#    #+#             */
/*   Updated: 2016/12/08 16:27:29 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p_server.h"

char	return_client_error(t_client_data *client, char *error)
{
	ft_client_error(client, error);
	return (0);
}

char	return_cd_error(t_client_data *client, char *dir, char *current_dir,
																char *error)
{
	chdir(current_dir);
	free(dir);
	free(current_dir);
	return (return_client_error(client, error));
}

char	handle_cd(t_client_data *client, t_options *options, char **args)
{
	char	*dir;
	char	*current_dir;

	(void)options;
	if (!args[1])
		return (return_client_error(client, "cd requires an argument"));
	current_dir = NULL;
	get_current_dir(&current_dir);
	if (!current_dir)
		return (return_client_error(client, "malloc error"));
	dir = args[1];
	if (chdir(dir) == -1)
		return (return_client_error(client, "bad dir"));
	get_current_dir(&dir);
	if (!dir)
		return (return_cd_error(client, dir, current_dir, "malloc error"));
	if (!ft_startswith(dir, client->launch_dir))
		return (return_cd_error(client, dir, current_dir, "no rights"));
	free(dir);
	free(current_dir);
	ft_client_success(client, "changed dir", ft_strlen("changed dir"));
	return (1);
}
