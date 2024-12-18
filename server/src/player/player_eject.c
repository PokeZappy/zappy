/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_eject.c
*/

#include "../../include/server.h"

int relative_push(player_t *pusher, player_t *pushed)
{
    int direction_map[4][4] = {
            {5, 3, 1, 7},
            {7, 5, 3, 1},
            {1, 7, 5, 3},
            {3, 1, 7, 5}
    };

    return direction_map[pusher->direction][pushed->direction];
}

void push_player(client_socket_t *pushed, player_t *pusher, server_t *server)
{
    int relative = relative_push(pusher, pushed->player);

    if (pusher->direction == UP)
        pushed->player->pos.y -= 1;
    if (pusher->direction == DOWN)
        pushed->player->pos.y += 1;
    if (pusher->direction == LEFT)
        pushed->player->pos.x -= 1;
    if (pusher->direction == RIGHT)
        pushed->player->pos.x += 1;
    dprintf(pushed->socket, "eject: %d\n", relative);
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "pex %d\n", pushed->id);
}

bool player_eject(server_t *server, player_t *player)
{
    client_socket_t *client;
    bool pushed = false;

    TAILQ_FOREACH(client, &server->head_client_sockets, entries) {
        if (!client->player)
            continue;
        if (client->player->pos.x == player->pos.x &&
        client->player->pos.y == player->pos.y) {
            push_player(client, player, server);
            pushed = true;
        }
    }
    return pushed;
}
