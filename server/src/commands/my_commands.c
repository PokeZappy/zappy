/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** my_commands.c
*/

#include "../../include/commands.h"
#include "../../include/utils.h"

void print_client_list(server_t *server)
{
    client_socket_t *client = TAILQ_FIRST(&server->_head_client_sockets);

    printf("CLIENT LIST:\n");
    while (client != NULL) {
        if (client->_is_gui == 1)
            printf("- GUI: {ID:%d}\n", client->_id);
        if (client->player != NULL) {
            printf("- CLIENT: {ID:%d}{TEAM_ID:%d}{TEAM:%s}{POS:%d-%d:%d}\n",
                client->_id, client->player->_id, client->player->_team->_name,
                client->player->_pos._x, client->player->_pos._y,
                client->player->_direction);
        }
        client = TAILQ_NEXT(client, entries);
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
