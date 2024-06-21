/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_eject.c
*/

#include "../../include/server.h"
#include "../../include/list.h"

int nb_player_on_tile(server_t *server, vector_t tile_pos)
{
    int nb = 0;
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);
    vector_t pos;

    while (current) {
        if (!current->player)
            continue;
        pos = current->player->_pos;
        if (pos._x == tile_pos._x && pos._y == tile_pos._y)
            nb++;
        current = TAILQ_NEXT(current, entries);
    }
    return nb;
}
