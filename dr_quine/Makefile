# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 18:40:30 by dbousque          #+#    #+#              #
#    Updated: 2016/06/10 17:19:32 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1	=	./Colleen/Colleen
NAME2	=	./Grace/Grace
NAME3	=	./Sully/Sully

WFLAGS	=	-Wall -Werror -Wextra

CC		=	gcc

SOURCE1	=	./Colleen/Colleen.c
SOURCE2	=	./Grace/Grace.c
SOURCE3	=	./Sully/Sully.c

OBJECT1	=	$(subst .c,.o,$(SOURCE1))
OBJECT2	=	$(subst .c,.o,$(SOURCE2))
OBJECT3	=	$(subst .c,.o,$(SOURCE3))

.SILENT:

all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1): $(OBJECT1)
	$(CC) $(WFLAGS) $(OBJECT1) -o $(NAME1)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

$(NAME2): $(OBJECT2)
	$(CC) $(WFLAGS) $(OBJECT2) -o $(NAME2)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

$(NAME3): $(OBJECT3)
	$(CC) $(WFLAGS) $(OBJECT3) -o $(NAME3)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

%.o: %.c
	$(CC) $(WFLAGS) -c -o $@ $^
	printf "\e[32m[✔]\e[36m $@ "
	printf "\033[0m\n"

clean:
	rm -Rf $(OBJECT1)
	rm -Rf $(OBJECT2)
	rm -Rf $(OBJECT3)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m Objects deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

fclean: clean
	rm -Rf $(NAME1)
	rm -Rf $(NAME2)
	rm -Rf $(NAME3)
	printf "\e[31m----------------------------------\n"
	printf "[✔]\e[36m All deleted\n"
	printf "\e[31m----------------------------------\e[36m"
	printf "\033[0m\n"

re: fclean all

PHONY: re fclean clean all
