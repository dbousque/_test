# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/02 12:22:16 by dbousque          #+#    #+#              #
#    Updated: 2016/01/02 12:30:03 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap
LIB		= libdodo
LIB_DIR	= $(LIB)/$(LIB).a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I. $(LIB_DIR) -I. ./$(LIB)/ -o $(NAME)

SRC		=	srcs/get_input.c \
			srcs/pile.c \
			srcs/pile2.c \
			srcs/main.c \
			srcs/push.c \
			srcs/reverse_rotate.c \
			srcs/rotate.c \
			srcs/swap.c

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
