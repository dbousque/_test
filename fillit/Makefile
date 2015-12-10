# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 10:27:09 by dbousque          #+#    #+#              #
#    Updated: 2015/12/03 19:00:27 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fillit

CC=gcc

CFLAGS=-Wall -Wextra -Werror -I. ./libft/libft.a -o fillit

RM=rm -f

SRC=./srcs/ft_dels.c ./srcs/ft_fillit.c ./srcs/ft_get_tetriminos.c \
	./srcs/ft_nodes.c ./srcs/ft_optimization.c \
	./srcs/ft_points.c ./srcs/ft_read_file.c ./srcs/ft_solve.c \
	./srcs/ft_strutils.c ./srcs/ft_strutils2.c ./srcs/ft_tree.c \
	./srcs/ft_treeutils.c ./srcs/ft_valid_tetrimino.c \
	./srcs/ft_valid_tetrimino2.c

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
