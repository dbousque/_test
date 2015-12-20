# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 10:27:09 by dbousque          #+#    #+#              #
#    Updated: 2015/12/20 17:09:01 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	alum1

CC=		gcc

CFLAGS=	-Wall -Wextra -Werror -I. ./libft/libft.a -o alum1

RM=		rm -f

SRC=	./srcs/moves.c \
		./srcs/alum1.c \
		./srcs/error_n_free.c \
		./srcs/utils.c \
		./srcs/get_board.c \
		./srcs/get_file_content.c \
		./srcs/get_next_line.c

$(NAME):
		make -C libft
		$(CC) $(CFLAGS) $(SRC)

all: $(NAME)

clean:
		make clean -C libft

fclean: clean
		make fclean -C libft
		$(RM) $(NAME)

re: fclean all
