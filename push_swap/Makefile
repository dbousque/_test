# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/02 12:22:16 by dbousque          #+#    #+#              #
#    Updated: 2016/01/05 18:02:44 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap
LIB		= libdodo
LIB_DIR	= $(LIB)/$(LIB).a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I. $(LIB_DIR) -o $(NAME)

SRC		=	srcs/get_input.c \
			srcs/pile.c \
			srcs/pile2.c \
			srcs/main.c \
			srcs/push.c \
			srcs/reverse_rotate.c \
			srcs/rotate.c \
			srcs/swap.c \
			srcs/apply_function.c \
			srcs/determ_sort2.c \
			srcs/determ_sort2_2.c \
			srcs/determ_sort2_3.c \
			srcs/free_utils.c \
			srcs/ft_tree.c \
			srcs/ft_treeutils.c \
			srcs/get_input_utils.c \
			srcs/last_move.c \
			srcs/looping_nodes.c \
			srcs/new_node.c \
			srcs/print_res.c \
			srcs/quicksort.c \
			srcs/quicksort2.c \
			srcs/reduce_best.c \
			srcs/score.c \
			srcs/scores_utils.c \
			srcs/tree_sort.c \
			srcs/utils.c

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
