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
	make -C serveur_dir

client:
	make -C client_dir

clean:
	make -C client_dir clean
	make -C serveur_dir clean

fclean:
	make -C client_dir fclean
	make -C serveur_dir fclean

re: fclean all

.PHONY: re fclean clean all client
