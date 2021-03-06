# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 16:58:25 by dbousque          #+#    #+#              #
#    Updated: 2018/04/28 19:35:15 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	wolf3d

SOURCES	=	srcs/compute_wolf3d.c \
			srcs/draw_debug.c \
			srcs/draw_ray_result.c \
			srcs/draw_ray_result2.c \
			srcs/draw_texture.c \
			srcs/draw_utils.c \
			srcs/events.c \
			srcs/init_wolf3d.c \
			srcs/interpret_blocks.c \
			srcs/interpret_map.c \
			srcs/interpret_textures.c \
			srcs/list.c \
			srcs/loop.c \
			srcs/main.c \
			srcs/read_config_file.c \
			srcs/read_tga.c \
			srcs/render_ray.c \
			srcs/threads_utils.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/valid_block.c \
			srcs/window.c

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIB_DIR	=	libmlx
endif
ifeq ($(UNAME_S), Darwin)
	LIB_DIR	=	libmlxosx
endif

LIB		=	$(LIB_DIR)/libmlx.a

LIB2_DIR=	libjson

LIB2	=	$(LIB2_DIR)/libjson.a

HEADERS	=	-I./includes/ -I./$(LIB_DIR) -I./$(LIB2_DIR) -I ~/libSOIL/src -I ~/.brew/include/SOIL

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra -O3

ifeq ($(UNAME_S), Linux)
	XLIB	=	-lXext -lX11 -lm -lSOIL -lGL
endif
ifeq ($(UNAME_S), Darwin)
	XLIB	=	-framework OpenGL -framework AppKit -lm -L ~/.brew/lib -lSOIL
endif

CC		=	clang

.SILENT:

$(NAME): $(OBJECTS)
	make -C $(LIB_DIR)
	make -C $(LIB2_DIR)
	$(CC) $(WFLAGS) $(OBJECTS) -o $(NAME) $(LIB) $(LIB2) $(XLIB) -lpthread
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

all: $(NAME)

%.o: %.c
	$(CC) $(WFLAGS) $(HEADERS) -c -o $@ $^
	printf "\e[32m[✔]\e[36m $@ "
	printf "\033[0m\n"

clean:
	make clean -C $(LIB_DIR)
	make clean -C $(LIB2_DIR)
	rm -Rf $(OBJECTS)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

fclean: clean
	rm -Rf $(NAME)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

PHONY: re fclean clean all
