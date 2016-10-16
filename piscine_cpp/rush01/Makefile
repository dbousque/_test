
export CC = clang++
export CFLAGS = -Wall -Wextra -Werror

NAME =	ft_gkrellm

SRC = 	main.cpp \
		CpuModule.cpp \
		DateModule.cpp \
		Field.cpp \
	 	HostnameModule.cpp \
		NetworkModule.cpp \
		OsInfosModule.cpp \
		RamModule.cpp \
		monitorGraphic.cpp \
		monitorShell.cpp \
		CatModule.cpp

NCURSES = -lncurses
BREW = -I ~/.brew/include/
SFML = -L ~/.brew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -rpath ~/.brew/lib

SRCO = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(SRCO)
	$(CC) $(CFLAGS) $(NCURSES) $(SFML) -o $(NAME) $(SRCO)
	@echo "\033[0;36m"$(NAME)" created\033[m"

clean:
	@rm -f $(SRCO)
	@echo "\033[0;32m"$(NAME)" objects cleaned\033[m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m"$(NAME)" cleaned\033[m"

re: fclean all

%.o: %.cpp
	$(CC) $(CFLAGS) $(BREW) -o $@ -c $<

.PHONY: all clean fclean re
