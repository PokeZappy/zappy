##
## EPITECH PROJECT, 2024
## HEADER
## File description:
## HEADER
##

SRC	=	./src/zappy_ai.py

NAME =	zappy_ai

$(NAME)	:
			cp $(SRC) ./
			mv zappy_ai.py zappy_ai

all: $(NAME)

clean:
		rm -rf zappy_ai

fclean:	clean

re:	fclean all

tests_run:
	pytest --cov=src/ tests/

.PHONY: all clean fclean re tests_run
