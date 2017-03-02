

NAME		=	a.out

SOURCES		=	srcs/shader_program.c \
				srcs/object.c \
				srcs/main.c \
				srcs/window.c \
				srcs/ft_itoa.c \
				srcs/matrices.c \
				srcs/events.c \
				srcs/camera.c \
				srcs/list.c \
				srcs/parse_face.c \
				srcs/parse_vertices.c \
				srcs/obj_parser.c \
				srcs/objfile_to_vertices.c \
				srcs/normals.c \
				srcs/main_utils.c \
				srcs/draw_objs.c \
				srcs/load_object_file.c \
				srcs/utils.c \
				srcs/utils2.c

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra -I includes

OS := $(shell uname)
ifneq ($(OS), Darwin)
FLAGS	=	-lSOIL -lGL -lGLU -lglut -lglfw3 -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lXinerama -lXcursor -lrt -lm -lGLEW
else
FLAGS	=	-framework OpenGL -lglfw -lGLEW -lSOIL
endif

CC		=	gcc

.SILENT:

$(NAME): $(OBJECTS)
	$(CC) $(WFLAGS) $(OBJECTS) -o $(NAME) $(FLAGS)
	printf "\e[32m----------------------------------\e[36m\n"
	printf "\e[32m[✔]\e[36m $@"
	printf "\n\e[32m----------------------------------\e[36m"
	printf "\033[0m\n"

all: $(NAME)

%.o: %.c
	$(CC) $(WFLAGS) -c -o $@ $^
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
