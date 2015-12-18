# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 10:27:09 by dbousque          #+#    #+#              #
#    Updated: 2015/12/18 17:50:48 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC=	ft_printf.c \
		ft_ntoa_base.c \
		ft_putaddr.c \
		ft_puthexa.c \
		ft_putlong.c \
		ft_putnbr_un.c \
		ft_putoctal.c

SRC2=	libft/ft_memset.c libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memccpy.c \
		libft/ft_memmove.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memalloc.c \
		libft/ft_memdel.c \
		libft/ft_strlen.c libft/ft_strdup.c libft/ft_strcpy.c libft/ft_strncpy.c libft/ft_strcat.c libft/ft_strncat.c \
		libft/ft_strlcat.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strstr.c libft/ft_strnstr.c \
		libft/ft_strcmp.c libft/ft_strncmp.c libft/ft_atoi.c \
		libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c \
		libft/ft_toupper.c libft/ft_tolower.c \
		libft/ft_strnew.c libft/ft_strdel.c libft/ft_strclr.c libft/ft_striter.c libft/ft_striteri.c \
		libft/ft_strmap.c libft/ft_strmapi.c libft/ft_strequ.c libft/ft_strnequ.c libft/ft_strsub.c libft/ft_strjoin.c \
		libft/ft_strtrim.c libft/ft_strsplit.c \
		libft/ft_itoa.c libft/ft_lstaddend.c libft/ft_putstrstr.c \
		libft/ft_putchar.c libft/ft_putstr.c libft/ft_putendl.c libft/ft_putnbr.c libft/ft_putchar_fd.c \
		libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
		libft/ft_lstadd.c libft/ft_lstdel.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstmap.c libft/ft_lstnew.c

SRC3=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
		ft_memdel.c \
		ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
		ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
		ft_strcmp.c ft_strncmp.c ft_atoi.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c \
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
		ft_strtrim.c ft_strsplit.c \
		ft_itoa.c ft_lstaddend.c ft_putstrstr.c \
		ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c



OBJ=$(SRC:.c=.o)

OBJ2=$(SRC3:.c=.o)

$(NAME): ft_printf.h
		$(CC) $(CFLAGS) -c $(SRC) $(SRC2)
		ar rc $(NAME) $(OBJ) $(OBJ2)
		ranlib $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJ)
		$(RM) $(OBJ2)

fclean: clean
		$(RM) $(NAME)

re: fclean all
