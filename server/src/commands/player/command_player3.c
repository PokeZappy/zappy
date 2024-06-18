/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player3.c
*/

#include "../../../include/commands.h"

static int calc_egg_id(server_t *server)
{
    int id = 0;
    egg_t *egg = TAILQ_FIRST(&server->_head_egg);

    while (egg != NULL) {
        id = egg->_id;
        egg = TAILQ_NEXT(egg, _entries);
    }
    return id + 1;
}

void cmd_fork(server_t *server, char *args, client_socket_t *client)
{
    int x = client->player->_pos._x;
    int y = client->player->_pos._y;
    egg_t *egg = (egg_t *)malloc(sizeof(egg_t));

    if (client->player->_team->_max_clients >= 1024) {
        free(egg);
        printf("ko\n");
        return;
    }
    client->player->_team->_max_clients += 1;
    egg->_available = 600;
    egg->_team = client->player->_team;
    egg->_pos = client->player->_pos;
    egg->_id = calc_egg_id(server);
    TAILQ_INSERT_TAIL(&server->grid->_tiles[x][y]->_head_egg, egg, _entries);
    TAILQ_INSERT_TAIL(&server->_head_egg, egg, _entries);
    dprintf(get_gui(server)->socket, "enw %d %d %d %d\n", egg->_id,
        client->_id, client->player->_pos._x, client->player->_pos._y);
    dprintf(client->socket, "ok\n");
}

void cmd_dead(server_t *server, char *args, client_socket_t *client)
{
    printf("dead\n");
}

void cmd_connect_nbr(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;

    if (!player)
        return;
    dprintf(client->socket, "%d\n",
    player->_team->_max_clients - player->_team->_current_clients);
    printf("connect_nbr\n");
}
