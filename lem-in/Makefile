NAME		=	lem-in

LIB_NAME	=	libdodo

SOURCES		=	srcs/get_fourmiliere.c \
				srcs/parse_salles.c \
				srcs/parse_salles2.c \
				srcs/parse_salles3.c \
				srcs/new_struct.c \
				srcs/get_tubes.c \
				srcs/utils.c \
				srcs/utils2.c \
				srcs/utils3.c \
				srcs/main.c \
				srcs/find_suitable_paths.c \
				srcs/find_best_paths.c \
				srcs/make_fourmi_travel.c \
				srcs/get_flags.c \
				srcs/print_fourmis.c

HEADERS	=	-I./includes/

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra

CC		=	gcc

.SILENT:

$(NAME): $(OBJECTS)
	make -C ./$(LIB_NAME)
	$(CC) $(WFLAGS) -L./libdodo/ -ldodo $(OBJECTS) -o $(NAME)
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
