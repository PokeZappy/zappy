/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** egg.c
*/

#include "../../include/server.h"

void check_eggs(server_t *server)
{
    egg_t *egg = TAILQ_FIRST(&server->_head_egg);

    while (egg != NULL) {
        if (egg->_available > 0) {
            egg->_available -= 1;
        }
        if (egg->_available == 0 && egg->_ismatthias == 0) {
            egg->_ismatthias = 1;
            egg->_team->_max_clients += 1;
        }
        egg = TAILQ_NEXT(egg, _entries);
    }
}
