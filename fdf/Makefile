# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfixot <rfixot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/15 11:07:03 by rfixot            #+#    #+#              #
#    Updated: 2015/12/17 17:44:39 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
LIB		= libft
LIB2	= libmlx
LIB_DIR	= $(LIB)/$(LIB).a
LIB_DIR2= $(LIB2)/$(LIB2).a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -framework OpenGL -framework AppKit -I. $(LIB_DIR) -I. $(LIB_DIR2) -o $(NAME)

SRC		=	srcs/color.c \
			srcs/draw.c \
			srcs/error.c \
			srcs/ft_get_mesh.c \
			srcs/ft_render.c \
			srcs/get_next_line.c \
			srcs/main.c \
			srcs/new_mlx.c \
			srcs/draw_utils.c \
			srcs/free_things.c \
			srcs/hooks.c \
			srcs/mouse_hook.c \
			srcs/read_utils.c \
			srcs/render_utils.c

$(NAME):
	make -C $(LIB)
	make -C $(LIB2)
	$(CC) $(CFLAGS) $(SRC)

all: $(NAME)

clean:
	make clean -C $(LIB)
	make clean -C $(LIB2)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean all
