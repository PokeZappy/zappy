##
## EPITECH PROJECT, 2024
##
## File description:
## Makefile
##

SRC = 	$(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

TESTS_SRC = $(SRC)
TESTS_SRC += $(wildcard tests/*.c)

TESTS_TARGET = unit_tests

TESTS_OBJS := $(TESTS_SRC:%.c=%.o)

NAME = zappy_server

CXXFLAGS = -Wall -Wextra -g3 -Iinclude
CXXFLAGS += -lpthread

LDLIBS += -L./criterion/lib -lcriterion

CC = g++

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) main.c $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

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