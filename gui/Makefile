##
## EPITECH PROJECT, 2024
##
## File description:
## Makefile
##

SRC = 	$(wildcard src/*.cpp)

OBJ = $(SRC:.cpp=.o)

TESTS_SRC = $(SRC)
TESTS_SRC += $(wildcard tests/*.cpp)

TESTS_TARGET = unit_tests

TESTS_OBJS := $(TESTS_SRC:%.cpp=%.o)

NAME = zappy_gui

CXXFLAGS = -Wall -Wextra -g3 -Iinclude
CXXFLAGS += -lpthread

LDLIBS += -L./criterion/lib -lcriterion

CC = g++

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) main.cpp $(OBJ) $(CXXFLAGS)
	mv $(NAME) ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ../$(NAME)

re: fclean all

tests_run: $(TESTS_OBJS) coverage
	$(CC) -o unit_tests $(TESTS_OBJS) $(CXXFLAGS) $(LDLIBS)
	./unit_tests

tests_clean: fclean
	rm -f $(TEST_OBJ)
	rm -f unit_test*

coverage:
	gcovr

.PHONY: all clean fclean re tests_run coverage