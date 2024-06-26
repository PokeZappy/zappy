/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** my_commands.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"
#include "../../../include/objects.h"

void hack_player_health(server_t *server, char *args, client_socket_t *client)
{
    int id = 0;
    int health = 0;
    client_socket_t *tmp = NULL;

    if (sscanf(args + 12, "%d %d", &id, &health) == 2) {
        tmp = find_client_by_socket(server, id);
        if (tmp != NULL)
            tmp->player->health = health;
    }
}

void kill_player(server_t *server, char *args, client_socket_t *client)
{
    client_socket_t *tmp = NULL;
    int id = 0;

    if (sscanf(args + 5, "%d", &id) == 1) {
        tmp = find_client_by_socket(server, id);
        TAILQ_REMOVE(&server->head_client_sockets, tmp, entries);
        close(tmp->socket);
    }
}

void hack_tile(server_t *server, char *args, client_socket_t *client)
{
    int x = 0;
    int y = 0;
    char item_name[100];
    int quantity;

    if (sscanf(args + 9, "%s %d %d %d", item_name, &quantity, &x, &y) != 4)
        return;
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if (strcmp(object_names[i], item_name) == 0)
            server->grid->tiles[y][x]->items[i] = quantity;
    }
    bct(server, (vector_t){x, y});
}

void hack_whole_tile(server_t *server, char *args, client_socket_t *client)
{
    int x = 0;
    int y = 0;
    int items[7] = {0};

    if (sscanf(args + 15, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d",
    &x, &y, &items[0], &items[1], &items[2], &items[3], &items[4],
    &items[5], &items[6]) == 9) {
        for (int i = 0; i < 7; i++)
            server->grid->tiles[y][x]->items[i] = items[i];
    }
    bct(server, (vector_t){x, y});
}

void hack_level(server_t *server, char *args, client_socket_t *client)
{
    int id = 0;
    int level = 0;
    client_socket_t *tmp = NULL;

    if (sscanf(args + 10, "%d %d", &id, &level) == 2) {
        tmp = find_client_by_socket(server, id);
        if (tmp != NULL)
            tmp->player->level = level;
    }
    dprintf(get_gui(server)->socket, "plv %d %d\n", id, level);
}
