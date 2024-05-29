/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** my_commands.c
*/

#include "../../include/commands.h"
#include "../../include/utils.h"

void print_client_list(client_socket_t *client, server_t *server)
{
    client_socket_t *current = TAILQ_FIRST(&server->_head_client_sockets);

    dprintf(client->socket, "CLIENT LIST:\n");
    while (current != NULL) {
        if (current->_is_gui == 1)
            dprintf(client->socket, "- GUI: {ID:%d}\n", current->_id);
        if (current->player != NULL) {
            dprintf(client->socket,
                "- CLIENT: {ID:%d}{TEAM_ID:%d}{TEAM:%s}{POS:%d-%d:%d}\n",
                current->_id, current->player->_id,
                    current->player->_team->_name,
                current->player->_pos._x, current->player->_pos._y,
                current->player->_direction);
        }
        current = TAILQ_NEXT(current, entries);
    }
}

void exit_command(client_socket_t *client, server_t *server)
{
    printf("Client requested exit {%d}\n", client->_id);
    close(client->socket);
    TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
    free_client(client);
}

void hack_player_pos(client_socket_t *client, server_t *server, char *args)
{
    int x = 0;
    int y = 0;

    if (sscanf(args, "%d %d", &x, &y)) {
        client->player->_pos._x = x;
        client->player->_pos._y = y;
    }
}

void hack_player_dir(client_socket_t *client, server_t *server, char *args)
{
    if (strcmp(args, "UP") == 0)
        client->player->_direction = UP;
    if (strcmp(args, "RIGHT") == 0)
        client->player->_direction = RIGHT;
    if (strcmp(args, "DOWN") == 0)
        client->player->_direction = DOWN;
    if (strcmp(args, "LEFT") == 0)
        client->player->_direction = LEFT;
}
