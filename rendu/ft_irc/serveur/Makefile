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

NAME	=	serveur

SOURCES	=	srcs/circular_buffer.c \
			srcs/commands.c \
			srcs/commands2.c \
			srcs/commands3.c \
			srcs/list.c \
			srcs/new_user.c \
			srcs/parse_message.c \
			srcs/read_user_input.c \
			srcs/server.c \
			srcs/utils2.c \
			srcs/utils3.c \
			srcs/utils4.c \
			srcs/utils5.c \
			srcs/utils6.c \
			srcs/utils7.c \
			srcs/utils.c \
			srcs/validation.c \
			srcs/write_user_output.c

HEADERS	=	-I./includes/

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra

CC		=	clang

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
