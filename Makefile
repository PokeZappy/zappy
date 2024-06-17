##
## EPITECH PROJECT, 2024
##
## File description:
## Makefile
##

all:
	$(MAKE) -C ./ai
	cp ./ai/zappy_ai ./zappy_ai
	$(MAKE) -C ./gui
	$(MAKE) -C ./server

clean:
	$(MAKE) -C ./ai clean
	$(MAKE) -C ./gui clean
	$(MAKE) -C ./server clean

fclean:
	$(MAKE) -C ./ai fclean
	rm -f zappy_ai
	$(MAKE) -C ./gui fclean
	$(MAKE) -C ./server fclean

re:
	$(MAKE) -C ./ai re
	$(MAKE) -C ./gui re
	$(MAKE) -C ./server re

tests_run:
	$(MAKE) -C ./ai	tests_run
	$(MAKE) -C ./gui tests_run
	$(MAKE) -C ./server	tests_run

tests_clean:
	$(MAKE) -C ./ai	tests_clean
	$(MAKE) -C ./gui tests_clean
	$(MAKE) -C ./server	tests_clean
