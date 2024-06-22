/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** my_commands.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void hack_player_health(server_t *server, char *args, client_socket_t *client)
{
    int id = 0;
    int health = 0;
    client_socket_t *tmp = NULL;

    if (sscanf(args + 12, "%d %d", &id, &health) == 2) {
        tmp = find_client_by_socket(server, id);
        if (tmp != NULL)
            tmp->player->_health = health;
    }
}

void kill_player(server_t *server, char *args, client_socket_t *client)
{
    client_socket_t *tmp = NULL;
    int id = 0;

    if (sscanf(args + 5, "%d", &id) == 1) {
        tmp = find_client_by_socket(server, id);
        TAILQ_REMOVE(&server->_head_client_sockets, tmp, entries);
        close(tmp->socket);
    }
}
