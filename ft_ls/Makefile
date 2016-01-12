# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 18:40:30 by dbousque          #+#    #+#              #
#    Updated: 2016/01/12 19:42:18 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls

LIB_NAME	=	libdodo

SOURCES		=	srcs/error.c \
				srcs/get_file_stats.c \
				srcs/get_flags.c \
				srcs/get_params.c \
				srcs/listdir.c \
				srcs/main.c \
				srcs/print_children.c \
				srcs/print_columns.c \
				srcs/print_details.c \
				srcs/print_details2.c \
				srcs/print_details3.c \
				srcs/print_params.c \
				srcs/quicksort.c \
				srcs/sort_children.c \
				srcs/utils.c

HEADERS	=	-I./includes/

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra

CC		=	gcc

.SILENT:

$(NAME): $(OBJECTS)
	make -C ./$(LIB_NAME)
	$(CC) $(WFLAGS) -L./libdodo/ -ldodo $(OBJECTS) -o $(NAME)
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
	make -C ./$(LIB_NAME) clean
	rm -Rf $(OBJECTS)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

fclean: clean
	make -C ./$(LIB_NAME) fclean
	rm -Rf $(NAME)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m $(NAME): All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

PHONY: re fclean clean all
