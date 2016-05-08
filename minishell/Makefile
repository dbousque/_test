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

NAME		=	minishell

LIB_NAME	=	libft

SOURCES		=	srcs/autocomplete.c \
				srcs/autocomplete_utils.c \
				srcs/autocomplete_utils2.c \
				srcs/builtins.c \
				srcs/builtins2.c \
				srcs/find_executable.c \
				srcs/find_executable2.c \
				srcs/find_executable3.c \
				srcs/find_executable4.c \
				srcs/general_utils.c \
				srcs/get_input.c \
				srcs/input_utils.c \
				srcs/interpret_command.c \
				srcs/interpret_utils.c \
				srcs/linked_list.c \
				srcs/minishell.c \
				srcs/read_chars.c \
				srcs/read_chars_utils.c \
				srcs/split_in_args.c \
				srcs/split_in_args2.c \
				srcs/split_in_command.c

HEADERS	=	-I./includes/

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra

CC		=	gcc

.SILENT:

$(NAME): $(OBJECTS)
	make -C ./$(LIB_NAME)
	$(CC) $(WFLAGS) -L./libft/ -lft $(OBJECTS) -o $(NAME)
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
