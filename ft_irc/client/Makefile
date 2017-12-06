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

NAME	=	client

SOURCES	=	srcs/client.c \
			srcs/connect_to_server.c \
			srcs/parse_message.c \
			srcs/read_user_input.c \
			srcs/read_user_input2.c \
			srcs/update_info.c \
			srcs/utils.c \
			srcs/utils2.c \
			srcs/windows.c \
			srcs/wwrite.c \
			srcs/wwrite2.c

HEADERS	=	-I./includes/

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra

CC		=	clang

.SILENT:

$(NAME): $(OBJECTS)
	$(CC) $(WFLAGS) $(OBJECTS) -o $(NAME) -lncurses
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
