/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** find_by_socket.c
*/

#include "../../../include/server.h"

client_socket_t *find_client_by_player(server_t *server, player_t *player)
{
    client_socket_t *current = TAILQ_FIRST(&server->head_client_sockets);

    TAILQ_FOREACH(current, &server->head_client_sockets, entries) {
        if (current->player == player)
            return current;
    }
    return NULL;
}

client_socket_t *find_client_by_socket(server_t *server, int socket)
{
    client_socket_t *current = TAILQ_FIRST(&server->head_client_sockets);

    TAILQ_FOREACH(current, &server->head_client_sockets, entries) {
        if (current->player && current->id == socket)
            return current;
    }
    return NULL;
}

bool is_client_gui(client_socket_t *client)
{
    return client->player == NULL;
}
