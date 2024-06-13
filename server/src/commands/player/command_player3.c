/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player3.c
*/

#include "../../../include/commands.h"

void cmd_fork(server_t *server, char *args, client_socket_t *client)
{
    int x = client->player->_pos._x;
    int y = client->player->_pos._y;
    egg_t *egg = (egg_t *)malloc(sizeof(egg_t));

    client->player->_team->_max_clients += 1;
    egg->_available = 0;
    egg->_team = client->player->_team;
    egg->_pos = client->player->_pos;
    TAILQ_INSERT_TAIL(&server->grid->_tiles[x][y]->_head_egg, egg, _entries);
    printf("ok\n");
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
