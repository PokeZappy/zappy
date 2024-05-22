##
## EPITECH PROJECT, 2024
## B-YEP-400-LYN-4-1-zappy-tom.blancheton
## File description:
## Makefile
##

SRC = 	$(wildcard src/*.c) \
		$(wildcard src/**/*.c) \
		$(wildcard src/**/**/*.c)

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

ECHO = echo -e
GREEN = "\033[0;32m"
RED = "\033[0;31m"
BLUE = "\033[0;34m"
DEFAULT = "\033[0m"

all: $(NAME)

$(NAME):	$(OBJ)
	@ $(CC) -o $(NAME) main.c $(OBJ) $(CXXFLAGS) && \
	$(ECHO) $(GREEN) "ZAPPY_SERVER COMPILED" || \
	$(ECHO) $(RED) "ZAPPY_SERVER NON COMPILED"

clean:
	@ rm -f $(OBJ)
	@ $(ECHO) $(GREEN) "CLEANED"

fclean: clean
	@ rm -f $(NAME)
	@ $(ECHO) $(GREEN) "FCLEANED"

re: fclean all

tests_run: $(TESTS_OBJS) coverage
	$(CC) -o unit_tests $(TESTS_OBJS) $(CXXFLAGS) $(LDLIBS)
	./unit_tests

tests_clean: fclean
	rm -f $(TEST_OBJ)
	rm -f unit_test*

coverage:
	gcovr

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
        $(ECHO) $(GREEN) "[OK]" $(BLUE) $< $(DEFAULT) || \
        ($(ECHO) $(RED) "[XX]" $(BLUE) $< $(DEFAULT) && exit 1)

.PHONY: all clean fclean re tests_run coverage
