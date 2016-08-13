# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 18:40:30 by dbousque          #+#    #+#              #
#    Updated: 2016/01/13 19:15:51 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		=	libft_malloc_$(HOSTTYPE).so

SOURCES		=	srcs/alloc.c \
				srcs/alloc_small.c \
				srcs/alloc_tiny.c \
				srcs/calloc_reallocf.c \
				srcs/dump_malloc.c \
				srcs/free.c \
				srcs/free_small.c \
				srcs/free_tiny.c \
				srcs/ft_ntoa_base.c \
				srcs/linked_list.c \
				srcs/malloc.c \
				srcs/malloc2.c \
				srcs/print_malloc.c \
				srcs/print_malloc2.c \
				srcs/print_number.c \
				srcs/quicksort_zones.c \
				srcs/realloc.c \
				srcs/realloc_small.c \
				srcs/realloc_tiny.c \
				srcs/utils.c \
				srcs/utils2.c \
				srcs/utils3.c \
				srcs/utils4.c \
				srcs/utils_print.c \
				srcs/utils_print2.c \
				srcs/utils_print3.c

HEADERS	=	-I./includes/

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra

CC		=	gcc

.SILENT:

$(NAME): $(OBJECTS)
	$(CC) $(WFLAGS) $(OBJECTS) -shared -o $(NAME)
	ln -s $(NAME) libft_malloc.so
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
	rm -Rf $(OBJECTS)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

fclean: clean
	rm -Rf $(NAME)
	rm -Rf libft_malloc.so
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

PHONY: re fclean clean all
