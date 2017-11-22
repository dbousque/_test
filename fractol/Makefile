# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 16:58:25 by dbousque          #+#    #+#              #
#    Updated: 2016/12/08 17:07:13 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

SOURCES	=	srcs/events.c \
			srcs/fractals.c \
			srcs/main.c \
			srcs/palettes.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/window.c

LIB_DIR	=	libmlx

LIB		=	$(LIB_DIR)/$(LIB_DIR).a

HEADERS	=	-I./includes/ -I./$(LIB_DIR)

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra -O3

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	XLIB	=	-lXext -lX11
endif
ifeq ($(UNAME_S), Darwin)
	XLIB	=	-framework OpenGL -framework AppKit
endif

CC		=	clang

.SILENT:

$(NAME): $(OBJECTS)
	make -C libmlx
	$(CC) $(WFLAGS) $(OBJECTS) -o $(NAME) $(LIB) $(XLIB) -lpthread
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
	make clean -C libmlx
	rm -Rf $(OBJECTS)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

fclean: clean
	make clean -C libmlx
	rm -Rf $(NAME)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

PHONY: re fclean clean all
