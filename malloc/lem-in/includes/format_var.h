/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_var.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:28:03 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:15:11 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_VAR_H
# define FORMAT_VAR_H

# define BUF_SIZE 1024

typedef struct			s_file
{
	int					fd;
	char				*content;
}						t_file;

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

void					free_format(t_format *format);
t_format				*new_format(void);
int						get_next_line(int const fd, char **line);

#endif
