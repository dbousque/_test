

NAME		=	particle-system

SOURCES		=	hello.c \
				window.c \
				cl_buffer.c \
				utils.c \
				gl_buffer.c \
				gl_program.c \
				cl_program.c \
				input.c

OBJECTS	=	$(subst .c,.o,$(SOURCES))

WFLAGS	=	-Wall -Werror -Wextra -I includes -I ~/libSOIL

OS := $(shell uname)
ifneq ($(OS), Darwin)
FLAGS	=	-lOpenCL -lSOIL -lGL -lGLU -lglut -lglfw3 -lX11 -lXxf86vm -lXrandr -pthread -lXi -ldl -lXinerama -lXcursor -lrt -lm -lGLEW
else
FLAGS	=	-framework opencl -framework OpenGL -lglfw -lGLEW -lSOIL
endif

CC		=	clang

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
