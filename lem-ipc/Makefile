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

NAME		=	lemipc2

SOURCES		=	srcs/lem_ipc.c \
				srcs/utils.c \
				srcs/list.c \
				srcs/parse_params.c \
				srcs/msg_queue.c \
				srcs/lem_ipc_msg.c \
				srcs/shared_ressources.c \
				srcs/shared_ressources2.c \
				srcs/init_ressources.c \
				srcs/init_ressources2.c \
				srcs/player.c \
				srcs/player2.c \
				srcs/player3.c \
				srcs/make_move.c \
				srcs/is_surrounded.c \
				srcs/find_player_team.c \
				srcs/attack_strategy.c

HEADERS		=	-I./includes/

OBJECTS		=	$(subst .c,.o,$(SOURCES))

WFLAGS		=	-Wall -Werror -Wextra

CC			=	clang

.SILENT:

$(NAME): $(OBJECTS)
	$(CC) $(WFLAGS) -lpthread $(OBJECTS) -o $(NAME)
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
