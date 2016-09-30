/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 16:40:39 by dbousque          #+#    #+#             */
/*   Updated: 2016/09/29 16:41:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTS_H
# define LIBFTS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

void		ft_bzero(void *ptr, size_t size);
char		*ft_strcat(char *s1, const char *s2);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_puts(const char *str);
size_t		ft_strlen(const char *str);
size_t		ft_my_strlen(const char *str);
void		*ft_memset(void *ptr, int c, size_t len);
void		*ft_memcpy(void *dest, void *src, size_t n);
char		*ft_strdup(const char *str);
void		ft_cat(int fd);

#endif
