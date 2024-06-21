/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** my_commands.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

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

void hack_player_pos(server_t *server, char *args, client_socket_t *client)
{
    int x = 0;
    int y = 0;
    int id = 0;
    client_socket_t *tmp = NULL;

    if (sscanf(args + 9, "%d %d %d", &id, &x, &y)) {
        tmp = find_client_by_socket(server, id);
        if (tmp != NULL) {
            tmp->player->_pos._x = x;
            tmp->player->_pos._y = y;
        }
    }
}

void hack_player_dir(server_t *server, char *args, client_socket_t *client)
{
    int id = 0;
    char dir[16];
    client_socket_t *tmp = NULL;

    if (sscanf(args + 9, "%d %15s", &id, dir) == 2) {
        tmp = find_client_by_socket(server, id);
        if (tmp == NULL)
            return;
        if (strcmp(dir, "UP") == 0)
            tmp->player->_direction = UP;
        if (strcmp(dir, "RIGHT") == 0)
            tmp->player->_direction = RIGHT;
        if (strcmp(dir, "DOWN") == 0)
            tmp->player->_direction = DOWN;
        if (strcmp(dir, "LEFT") == 0)
            tmp->player->_direction = LEFT;
    }
}

void print_egg_list(server_t *server, char *args, client_socket_t *client)
{
    egg_t *egg = TAILQ_FIRST(&server->_head_egg);

    dprintf(client->socket, "EGG_LIST:\n");
    while (egg != NULL) {
        dprintf(client->socket, "{%d, %d}: [TEAM:%s | CYCLE:%d | ID:%d]",
            egg->_pos._x, egg->_pos._y, egg->_team->_name, egg->_available,
            egg->_id);
        egg = TAILQ_NEXT(egg, _entries);
        dprintf(client->socket, "\n");
    }
}

void hack_player_give(server_t *server, char *args, client_socket_t *client)
{
    int id = 0;
    int resource = 0;
    int quantity = 0;
    client_socket_t *tmp = NULL;

    if (sscanf(args + 10, "%d %d %d", &id, &resource, &quantity) == 3) {
        tmp = find_client_by_socket(server, id);
        if (tmp != NULL)
            tmp->player->_inventory[resource] += 1;
    }
}
