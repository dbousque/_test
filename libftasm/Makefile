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

SRCS=	srcs/ft_bzero.s \
		srcs/ft_cat.s \
		srcs/ft_isalnum.s \
		srcs/ft_isalpha.s \
		srcs/ft_isascii.s \
		srcs/ft_isdigit.s \
		srcs/ft_isprint.s \
		srcs/ft_memcpy.s \
		srcs/ft_memset.s \
		srcs/ft_puts.s \
		srcs/ft_strcat.s \
		srcs/ft_strdup.s \
		srcs/ft_strlen.s \
		srcs/ft_tolower.s \
		srcs/ft_toupper.s

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