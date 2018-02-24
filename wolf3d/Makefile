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

NAME	=	wolf3d

SOURCES	=	srcs/events.c \
			srcs/main.c \
			srcs/utils.c \
			srcs/window.c

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIB_DIR	=	libmlx
endif
ifeq ($(UNAME_S), Darwin)
	LIB_DIR	=	libmlxosx
endif

LIB		=	$(LIB_DIR)/libmlx.a

HEADERS	=	-I./includes/ -I./$(LIB_DIR)

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra -O3

ifeq ($(UNAME_S), Linux)
	XLIB	=	-lXext -lX11 -lm
endif
ifeq ($(UNAME_S), Darwin)
	XLIB	=	-framework OpenGL -framework AppKit -lm
endif

CC		=	clang

.SILENT:

$(NAME): $(OBJECTS)
	make -C $(LIB_DIR)
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
	make clean -C $(LIB_DIR)
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
