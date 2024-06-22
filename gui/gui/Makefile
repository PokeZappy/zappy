##
## EPITECH PROJECT, 2024
##
## File description:
## Makefile
##

SRC				=	main.cpp							\
					$(wildcard src/*.cpp)				\
					$(wildcard src/raylib/*.cpp)		\
					$(wildcard src/raylib/debug/*.cpp)	\
					$(wildcard src/raylib/hud/*.cpp)	\
					$(wildcard src/sfml/*.cpp)	\
					$(wildcard src/world/*.cpp)


OBJ				=	$(SRC:.cpp=.o)
DEPS			=	$(SRC:.cpp=.d)

TESTS_SRC		=	$(SRC)
TESTS_SRC		+=	$(wildcard tests/*.cpp)

TESTS_TARGET	=	unit_tests

TESTS_OBJS		:=	$(TESTS_SRC:%.cpp=%.o)

NAME			=	zappy_gui

INCLUDEFLAGS	=	-Iinclude					\
					-Iinclude/graphics/sfml		\
					-Iinclude/world				\
					-Iinclude/graphics/raylib	\
					-Iinclude/graphics			\
					-I./lib/include				\
					-I./lib/raylib/src			\
					-I./lib/raylib-cpp/include	\
					$(shell pkg-config --cflags libconfig++)
CXXFLAGS		=	-std=c++20 -Wall -Wextra -g3 $(INCLUDEFLAGS)
LDFLAGS			=	$(shell pkg-config --libs libconfig++)		\
					$(shell pkg-config --libs sfml-graphics)	\
					-L./lib/raylib/src -lraylib -lpthread -ldl
DEPSFLAGS		=	-MMD -MP

LDLIBS			+=	-L./criterion/lib -lcriterion

CC = g++

MACBREWSFML		= 	/opt/homebrew/Cellar/sfml/2.6.1

MACSFMLINCLUDE	=	-I$(MACBREWSFML)/include
MACSFMLLIB		=	-L$(MACBREWSFML)/lib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += $(MACSFMLINCLUDE) -mmacosx-version-min=10.15
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
	@$(MAKE) -C lib/raylib/src
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
	#$(CC) -o unit_tests $(TESTS_OBJS) $(CXXFLAGS) $(LDLIBS)
	#./unit_tests

tests_clean: fclean
	rm -f $(TEST_OBJ)
	rm -f unit_test*

coverage:
	gcovr

.PHONY: all clean fclean re tests_run coverage dbg dbgs
