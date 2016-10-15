NAME = test
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
INC= -I ~/.brew/include 
LIBS= -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl

.PHONY= all re fclean clean

all: $(NAME) 

$(NAME): $(OBJ) 
	clang++ -Wall -Werror -Wextra -o $@ $(OBJ) $(LIBS) $(INC) 

%.o: %.cpp 
	clang++ -g -Wall -Werror -Wextra -o $@ -c $< $(INC)

re: fclean all

fclean: clean
	rm $(NAME)
	
clean:
	rm $(OBJ)
