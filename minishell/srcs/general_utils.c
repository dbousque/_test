/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:39:48 by dbousque          #+#    #+#             */
/*   Updated: 2016/05/08 17:39:50 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_error(void)
{
	ft_putstr("Could not allocate memory.\n");
	exit(1);
}

void	print_prompt(char **env)
{
	char	*current_dir;

	ft_putstr(get_logname(env));
	ft_putstr(":");
	current_dir = get_current_dir();
	ft_putstr("[0;36;40m");
	ft_putstr(current_dir);
	ft_putstr("[0m");
	free(current_dir);
	ft_putstr("$> ");
}
