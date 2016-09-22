# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 18:40:30 by dbousque          #+#    #+#              #
#    Updated: 2016/01/13 12:25:10 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_nm

SOURCES		=	srcs/fat.c \
				srcs/ft_atoi.c \
				srcs/ft_ntoa_base.c \
				srcs/get_n_sect.c \
				srcs/list.c \
				srcs/mach_o_32.c \
				srcs/mach_o_64.c \
				srcs/main.c \
				srcs/mergesort.c \
				srcs/mmap.c \
				srcs/my_malloc.c \
				srcs/my_malloc2.c  \
				srcs/nm.c \
				srcs/print_symbol.c \
				srcs/print_symbol2.c \
				srcs/quicksort.c \
				srcs/ran.c \
				srcs/ran_utils.c \
				srcs/read_options.c \
				srcs/simple_sort.c \
				srcs/utils.c \
				srcs/utils2.c \
				srcs/utils3.c


HEADERS	=	-I./includes/

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra

CC		=	gcc

.SILENT:

$(NAME): $(OBJECTS)
	$(CC) $(WFLAGS) $(OBJECTS) -o $(NAME)
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
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

PHONY: re fclean clean all
