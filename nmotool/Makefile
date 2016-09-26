# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 18:40:30 by dbousque          #+#    #+#              #
#    Updated: 2016/09/26 18:40:49 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C ft_nm all
	make -C ft_otool all

clean:
	make -C ft_nm clean
	make -C ft_otool clean

fclean:
	make -C ft_nm fclean
	make -C ft_otool fclean

re: fclean all

ft_nm:
	make -C ft_nm all

ft_otool:
	make -C ft_otool all

.PHONY: re fclean clean all ft_nm ft_otool
