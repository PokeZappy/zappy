/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** egg.c
*/

#include "../../include/server.h"

void check_eggs(server_t *server)
{
    egg_t *egg = TAILQ_FIRST(&server->head_egg);

    while (egg != NULL) {
        if (egg->available > 0) {
            egg->available -= 1;
        }
        if (egg->available == 0 && egg->is_matthias == 0) {
            egg->is_matthias = 1;
            egg->team->max_clients += 1;
        }
        egg = TAILQ_NEXT(egg, entries);
    }
}
