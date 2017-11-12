# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 17:09:09 by dbousque          #+#    #+#              #
#    Updated: 2016/12/08 18:47:26 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: client serveur

serveur:
	make -C serveur

client:
	make -C client

clean:
	make -C client clean
	make -C serveur clean

fclean:
	make -C client fclean
	make -C serveur fclean

re: fclean all

.PHONY: re fclean clean all client serveur
