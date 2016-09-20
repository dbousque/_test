# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 10:27:09 by dbousque          #+#    #+#              #
#    Updated: 2016/01/02 12:12:13 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	libfts.a

RM=		rm -f

SRCS=	srcs/bzero.s \
		srcs/cat.s \
		srcs/isalnum.s \
		srcs/isalpha.s \
		srcs/isascii.s \
		srcs/isdigit.s \
		srcs/isprint.s \
		srcs/memcpy.s \
		srcs/memset.s \
		srcs/puts.s \
		srcs/strcat.s \
		srcs/strdup.s \
		srcs/strlen.s \
		srcs/tolower.s \
		srcs/toupper.s

OBJS=	$(subst .s,.o,$(SRCS))

NASM=	nasm

FLAGS=	-f macho64

$(NAME): $(OBJS)
		ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

all: $(NAME)

%.o: %.s
	$(NASM) $(FLAGS) $^

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

PHONY: re fclean clean all