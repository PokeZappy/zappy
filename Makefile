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
	@ cp ./server/zappy_server ./

ai:
	$(MAKE) -C ./ai
	cp ./ai/zappy_ai ./zappy_ai

gui:
	$(MAKE) -C ./gui

server:
	$(MAKE) -C ./server
	@ cp ./server/zappy_server ./

clean:
	$(MAKE) -C ./ai clean
	$(MAKE) -C ./gui clean
	$(MAKE) -C ./server clean

fclean:
	$(MAKE) -C ./ai fclean
	rm -f zappy_ai
	$(MAKE) -C ./gui fclean
	$(MAKE) -C ./server fclean
	@ rm -f zappy_server

re:
	$(MAKE) -C ./ai re
	$(MAKE) -C ./gui re
	$(MAKE) -C ./server re
	@ cp ./server/zappy_server ./

tests_run:
	PYTHONPATH=$(shell pwd):$$PYTHONPATH $(MAKE) -C ./ai tests_run
	$(MAKE) -C ./gui tests_run
	$(MAKE) -C ./server	tests_run

ai_tests:
	PYTHONPATH=$(shell pwd):$$PYTHONPATH $(MAKE) -C ./ai tests_run

gui_tests:
	$(MAKE) -C ./gui tests_run

server_tests:
	$(MAKE) -C ./server	tests_run

tests_clean:
	$(MAKE) -C ./ai	tests_clean
	$(MAKE) -C ./gui tests_clean
	$(MAKE) -C ./server	tests_clean
