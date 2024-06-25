/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_eject.c
*/

#include "../../include/server.h"
#include "../../include/list.h"

int nb_player_on_tile(server_t *server, vector_t tilepos)
{
    int nb = 0;
    client_socket_t *current = TAILQ_FIRST(&server->head_client_sockets);
    vector_t pos;

    while (current) {
        if (!current->player) {
            current = TAILQ_NEXT(current, entries);
            continue;
        }
        pos = current->player->pos;
        if (pos.x == tilepos.x && pos.y == tilepos.y)
            nb++;
        current = TAILQ_NEXT(current, entries);
    }
    return nb;
}
