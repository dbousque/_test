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

NAME	=	libjson.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

SRC		=	srcs/get_helpers.c \
			srcs/get_helpers2.c \
			srcs/handle_x.c \
			srcs/handle_x2.c \
			srcs/json.c \
			srcs/json2.c \
			srcs/json_errors.c \
			srcs/print_utils.c \
			srcs/read_free_json.c \
			libdodo_srcs/arg_put2.c \
			libdodo_srcs/arg_put3.c \
			libdodo_srcs/arg_put4.c \
			libdodo_srcs/arg_put.c \
			libdodo_srcs/color.c \
			libdodo_srcs/format_var.c \
			libdodo_srcs/ft_atod.c \
			libdodo_srcs/ft_atoi.c \
			libdodo_srcs/ft_atol.c \
			libdodo_srcs/ft_bzero.c \
			libdodo_srcs/ft_isalnum.c \
			libdodo_srcs/ft_isalpha.c \
			libdodo_srcs/ft_isascii.c \
			libdodo_srcs/ft_isdigit.c \
			libdodo_srcs/ft_isprint.c \
			libdodo_srcs/ft_itoa.c \
			libdodo_srcs/ft_lstadd.c \
			libdodo_srcs/ft_lstaddend.c \
			libdodo_srcs/ft_lstdel.c \
			libdodo_srcs/ft_lstdelone.c \
			libdodo_srcs/ft_lstiter.c \
			libdodo_srcs/ft_lstmap.c \
			libdodo_srcs/ft_lstnew.c \
			libdodo_srcs/ft_memalloc.c \
			libdodo_srcs/ft_memccpy.c \
			libdodo_srcs/ft_memchr.c \
			libdodo_srcs/ft_memcmp.c \
			libdodo_srcs/ft_memcpy.c \
			libdodo_srcs/ft_memdel.c \
			libdodo_srcs/ft_memmove.c \
			libdodo_srcs/ft_memset.c \
			libdodo_srcs/ft_ntoa_base.c \
			libdodo_srcs/ft_printf.c \
			libdodo_srcs/ft_putaddr.c \
			libdodo_srcs/ft_putbinary.c \
			libdodo_srcs/ft_putchar.c \
			libdodo_srcs/ft_putchar_fd.c \
			libdodo_srcs/ft_putdouble.c \
			libdodo_srcs/ft_putendl.c \
			libdodo_srcs/ft_putendl_fd.c \
			libdodo_srcs/ft_puthexa.c \
			libdodo_srcs/ft_putlong.c \
			libdodo_srcs/ft_putnbr.c \
			libdodo_srcs/ft_putnbr_fd.c \
			libdodo_srcs/ft_putnbr_un.c \
			libdodo_srcs/ft_putoctal.c \
			libdodo_srcs/ft_putstr.c \
			libdodo_srcs/ft_putstr_fd.c \
			libdodo_srcs/ft_putstrstr.c \
			libdodo_srcs/ft_putstr_unprint.c \
			libdodo_srcs/ft_putunicode.c \
			libdodo_srcs/ft_putwchar2.c \
			libdodo_srcs/ft_putwchar.c \
			libdodo_srcs/ft_strcat.c \
			libdodo_srcs/ft_strchr.c \
			libdodo_srcs/ft_strclr.c \
			libdodo_srcs/ft_strcmp.c \
			libdodo_srcs/ft_strcpy.c \
			libdodo_srcs/ft_strdel.c \
			libdodo_srcs/ft_strdup.c \
			libdodo_srcs/ft_strequ.c \
			libdodo_srcs/ft_striter.c \
			libdodo_srcs/ft_striteri.c \
			libdodo_srcs/ft_strjoin.c \
			libdodo_srcs/ft_strlcat.c \
			libdodo_srcs/ft_strlen.c \
			libdodo_srcs/ft_strmap.c \
			libdodo_srcs/ft_strmapi.c \
			libdodo_srcs/ft_strncat.c \
			libdodo_srcs/ft_strncmp.c \
			libdodo_srcs/ft_strncpy.c \
			libdodo_srcs/ft_strnequ.c \
			libdodo_srcs/ft_strnew.c \
			libdodo_srcs/ft_strnstr.c \
			libdodo_srcs/ft_strrchr.c \
			libdodo_srcs/ft_strsplit.c \
			libdodo_srcs/ft_strstr.c \
			libdodo_srcs/ft_strsub.c \
			libdodo_srcs/ft_strtrim.c \
			libdodo_srcs/ft_tolower.c \
			libdodo_srcs/ft_toupper.c \
			libdodo_srcs/ft_unicode_utils.c \
			libdodo_srcs/get_arg.c \
			libdodo_srcs/get_flags.c \
			libdodo_srcs/get_next_line.c \
			libdodo_srcs/get_precision.c \
			libdodo_srcs/get_width_n_length.c \
			libdodo_srcs/parse_format.c \
			libdodo_srcs/precision2.c \
			libdodo_srcs/precision.c \
			libdodo_srcs/print_format.c \
			libdodo_srcs/read_whole_file.c \
			libdodo_srcs/sharp.c \
			libdodo_srcs/utils2.c \
			libdodo_srcs/utils.c \
			libdodo_srcs/width.c

OBJ		=	$(SRC:.c=.o)

HEADERS	=	-I./

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
			ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $^
	printf "\e[32m[✔]\e[36m $@ "
	printf "\033[0m\n"

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
