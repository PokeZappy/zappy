/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player3.c
*/

#include "../../../include/commands.h"

static int calc_eggid(server_t *server)
{
    int id = 0;
    egg_t *egg = TAILQ_FIRST(&server->head_egg);

    while (egg != NULL) {
        id = egg->id;
        egg = TAILQ_NEXT(egg, entries);
    }
    return id + 1;
}

static void create_egg(egg_t *egg, client_socket_t *client, server_t *server)
{
    egg->is_matthias = 0;
    egg->available = 600;
    egg->team = client->player->team;
    egg->pos = client->player->pos;
    egg->client_id = client->id;
    egg->id = calc_eggid(server);
}

void cmd_fork(server_t *server, char *args, client_socket_t *client)
{
    int x = client->player->pos.x;
    int y = client->player->pos.y;
    egg_t *egg = (egg_t *)malloc(sizeof(egg_t));

    if (client->player->team->max_clients >= 1024) {
        free(egg);
        return;
    }
    create_egg(egg, client, server);
    TAILQ_INSERT_TAIL(&server->grid->tiles[x][y]->head_egg, egg, entries);
    TAILQ_INSERT_TAIL(&server->head_egg, egg, entries);
    if (get_gui(server))
        dprintf(get_gui(server)->socket, "enw %d %d %d %d\n", egg->id,
        client->id, client->player->pos.x, client->player->pos.y);
    dprintf(client->socket, "ok\n");
}

void cmd_connect_nbr(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;

    if (!player)
        return;
    dprintf(client->socket, "%d\n",
    player->team->max_clients - player->team->current_clients);
}
