##
## EPITECH PROJECT, 2024
##
## File description:
## Makefile
##

SRC				=	main.cpp	\
					$(wildcard src/*.cpp)

OBJ				=	$(SRC:.cpp=.o)
DEPS			=	$(SRC:.cpp=.d)

TESTS_SRC		=	$(SRC)
TESTS_SRC		+=	$(wildcard tests/*.cpp)

TESTS_TARGET	=	unit_tests

TESTS_OBJS		:=	$(TESTS_SRC:%.cpp=%.o)

NAME			=	zappy_gui

DBGFLAGS		=	-g3 -O0
CXXFLAGS		=	-std=c++20 -Wall -Wextra -g3 -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS		+=	-lpthread
DEPSFLAGS		=	-MMD -MP


LDLIBS			+=	-L./criterion/lib -lcriterion

CC = g++

all: $(NAME)

dbg: CXXFLAGS += $(DBGFLAGS)
dbg: all

dbgs: CFLAGS += $(DBGFLAGS) -fsanitize=address
dbgs: $(NAME)

-include $(DEPS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(DEPSFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)
	cp $(NAME) ../

clean:
	rm -f $(OBJ)
	rm -f $(DEPS)

fclean: clean
	rm -f ../$(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

tests_run: $(TESTS_OBJS) coverage
	$(CC) -o unit_tests $(TESTS_OBJS) $(CXXFLAGS) $(LDLIBS)
	./unit_tests

tests_clean: fclean
	rm -f $(TEST_OBJ)
	rm -f unit_test*

coverage:
	gcovr

.PHONY: all clean fclean re tests_run coverage dbg dbgs
