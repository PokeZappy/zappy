/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** find_by_socket.c
*/

#include "../../../include/server.h"

client_socket_t *find_client_by_player(server_t *server, player_t *player)
{
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);

    TAILQ_FOREACH(current, &server->_head_client_sockets, entries) {
        if (current->player == player)
            return current;
    }
    return NULL;
}

client_socket_t *find_client_by_socket(server_t *server, int socket)
{
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);

    TAILQ_FOREACH(current, &server->_head_client_sockets, entries) {
        if (current->player && current->_id == socket)
            return current;
    }
    return NULL;
}

player_t *find_player_by_socket(server_t *server, int socket)
{
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);

    TAILQ_FOREACH(current, &server->_head_client_sockets, entries) {
        if (current->player && current->_id == socket)
            return current->player;
    }
    return NULL;
}

client_socket_t *find_gui(server_t *server, int socket)
{
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);

    while (current) {
        if (!current->player)
            return current;
        current = TAILQ_NEXT(current, entries);
    }
    return NULL;
}

bool is_client_gui(client_socket_t *client)
{
    return client->player == NULL;
}
