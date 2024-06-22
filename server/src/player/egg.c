/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** egg.c
*/

#include "../../include/server.h"

void check_eggs(server_t *server)
{
    egg_t *egg;

    TAILQ_FOREACH(egg, &server->_head_egg, _entries) {
        if (egg->_available > 0) {
            egg->_available -= 1;
        }
    }
}
