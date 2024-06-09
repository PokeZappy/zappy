/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_eject.c
*/

#include "../../include/server.h"

void push_player(client_socket_t *pushed, player_t *pusher)
{
    if (pusher->_direction == UP)
        pushed->player->_pos._y -= 1;
    if (pusher->_direction == DOWN)
        pushed->player->_pos._y += 1;
    if (pusher->_direction == LEFT)
        pushed->player->_pos._x -= 1;
    if (pusher->_direction == RIGHT)
        pushed->player->_pos._x += 1;
    dprintf(pushed->socket, "eject: %d\n", pusher->_direction);
}

bool player_eject(server_t *server, player_t *player)
{
    client_socket_t *client;
    bool pushed = false;

    TAILQ_FOREACH(client, &server->_head_client_sockets, entries) {
        if (!client->player)
            continue;
        if (client->player->_pos._x == player->_pos._x && client->player->_pos._y == player->_pos._y) {
            push_player(client, player);
            pushed = true;
        }
    }
    return pushed;
}
