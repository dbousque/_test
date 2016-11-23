# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/12 18:40:30 by dbousque          #+#    #+#              #
#    Updated: 2016/11/23 17:24:34 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	n-puzzle

SOURCES		=	Board.ml \
				Parse.ml \
				PriorityQueue.ml \
				Solve.ml

INTERF	=	$(subst .ml,.mli,$(SOURCES))

OBJS1	=	$(subst .ml,.cmi,$(SOURCES))

OBJS2	=	$(subst .ml,.cmx,$(SOURCES))

OBJS3	=	$(subst .ml,.o,$(SOURCES))

CC		=	ocamlopt

.SILENT:

all: $(NAME)

$(NAME):
	cd srcs && \
	for inter in $(INTERF) ; do \
		$(CC) $$inter ; \
	done && \
	$(CC) unix.cmxa $(SOURCES) Main.ml -o ../$(NAME)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

%.mli: %.ml
	cd srcs && \
	$(CC) $^
	printf "\e[32m[✔]\e[36m $@ "
	printf "\033[0m\n"

clean:
	cd srcs && \
	rm -Rf $(OBJS1) && \
	rm -Rf $(OBJS2) && \
	rm -Rf $(OBJS3) && \
	rm -Rf Main.cmi && \
	rm -Rf Main.cmx
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

