##
## EPITECH PROJECT, 2024
##
## File description:
## Makefile
##

SRC				=	main.cpp					\
					$(wildcard src/*.cpp)		\
					$(wildcard src/sfml/*.cpp)	\
					$(wildcard src/world/*.cpp)


OBJ				=	$(SRC:.cpp=.o)
DEPS			=	$(SRC:.cpp=.d)

TESTS_SRC		=	$(SRC)
TESTS_SRC		+=	$(wildcard tests/*.cpp)

TESTS_TARGET	=	unit_tests

TESTS_OBJS		:=	$(TESTS_SRC:%.cpp=%.o)

NAME			=	zappy_gui

INCLUDEFLAGS	=	-Iinclude -Iinclude/sfml -Iinclude/world
DBGFLAGS		=	-g3 -O0
CXXFLAGS		=	-std=c++20 -Wall -Wextra -g3 -Iinclude
LDFLAGS			=	-lsfml-graphics -lsfml-window -lsfml-system
DEPSFLAGS		=	-MMD -MP

LDLIBS			+=	-L./criterion/lib -lcriterion

CC = g++

MACBREWSFML		= 	/opt/homebrew/Cellar/sfml/2.6.1

MACSFMLINCLUDE	=	-I$(MACBREWSFML)/include
MACSFMLLIB		=	-L$(MACBREWSFML)/lib

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += $(MACSFMLINCLUDE)
	LDFLAGS += $(MACSFMLLIB)
endif

all: $(NAME)

dbg: CXXFLAGS += $(DBGFLAGS)
dbg: all

dbgs: CFLAGS += $(DBGFLAGS) -fsanitize=address
dbgs: $(NAME)

-include $(DEPS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(DEPSFLAGS) -c $< -o $@ $(LDFLAGS)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS)
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
