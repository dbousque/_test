# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/02 12:22:16 by dbousque          #+#    #+#              #
#    Updated: 2016/01/08 16:46:18 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem-in
LIB		= libdodo
LIB_DIR	= $(LIB)/$(LIB).a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I. $(LIB_DIR) -o $(NAME)

SRC		=	srcs/get_fourmiliere.c \
			srcs/parse_salles.c \
			srcs/parse_salles2.c \
			srcs/parse_salles3.c \
			srcs/new_struct.c

$(NAME):
	make -C $(LIB)
	$(CC) $(CFLAGS) $(SRC)

all: $(NAME)

clean:
	make clean -C $(LIB)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean all
