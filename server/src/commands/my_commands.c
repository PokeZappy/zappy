/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** my_commands.c
*/

#include "../../include/commands.h"
#include "../../include/utils.h"

void print_client_list(server_t *server, char *args, client_socket_t *client)
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

void exit_command(server_t *server, char *args, client_socket_t *client)
{
    printf("Client requested exit {%d}\n", client->_id);
    close(client->socket);
    TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
    free_client(client);
}

void hack_player_pos(server_t *server, char *args, client_socket_t *client)
{
    int x = 0;
    int y = 0;

    if (sscanf(args + 9, "%d %d", &x, &y)) {
        client->player->_pos._x = x;
        client->player->_pos._y = y;
    }
}

void hack_player_dir(server_t *server, char *args, client_socket_t *client)
{
    if (strcmp(args + 9, "UP") == 0)
        client->player->_direction = UP;
    if (strcmp(args + 9, "RIGHT") == 0)
        client->player->_direction = RIGHT;
    if (strcmp(args + 9, "DOWN") == 0)
        client->player->_direction = DOWN;
    if (strcmp(args + 9, "LEFT") == 0)
        client->player->_direction = LEFT;
}

void print_egg_list(server_t *server, char *args, client_socket_t *client)
{
    egg_t *egg = TAILQ_FIRST(&server->_head_egg);

    printf("EGG_LIST:\n");
    while (egg != NULL) {
        printf("{%d, %d}: [TEAM:%s | CYCLE:%d | ID:%d]", egg->_pos._x,
            egg->_pos._y, egg->_team->_name, egg->_available, egg->_id);
        egg = TAILQ_NEXT(egg, _entries);
        printf("\n");
    }
}
