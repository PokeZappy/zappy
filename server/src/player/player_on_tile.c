/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_eject.c
*/

#include "../../include/server.h"
#include "../../include/list.h"

list_t *get_player_on_tile(server_t *server, vector_t pos)
{
    list_t *same_tile_players = NULL;
    list_t *new_node;
    client_socket_t *client;

    for ((client) = ((&server->_head_client_sockets)->tqh_first); (client);
    (client) = ((client)->entries.tqe_next)) {
        if (client->player == NULL)
            continue;
        if (client->player->_pos._x == pos._x
        && client->player->_pos._y == pos._y) {
            new_node = (list_t *)malloc(sizeof(list_t));
            new_node->data = client->player;
            new_node->next = same_tile_players;
            same_tile_players = new_node;
        }
    }
    return same_tile_players;
}
