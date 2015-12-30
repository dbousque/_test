/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_var.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:28:03 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:28:33 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_VAR_H
# define FORMAT_VAR_H

typedef struct			s_format
{
	long long			value;
	unsigned long long	u_value;
	char				specifier;
	char				length;
	char				plus_flag;
	char				sharp_flag;
	char				space_flag;
	char				minus_flag;
	int					precision;
	int					width;
	char				neg_val;
	char				unsigned_val;
	char				has_sign;
	char				char_to_fill;
	char				characters;
}						t_format;

#endif
