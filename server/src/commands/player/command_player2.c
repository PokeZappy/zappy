/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player2.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

static void check_all_egg(tiles_t *tile, server_t *server)
{
    egg_t *egg = TAILQ_FIRST(&tile->head_egg);

    while (egg != NULL) {
        if (get_gui(server))
            dprintf(get_gui(server)->socket, "edi %d\n", egg->id);
        TAILQ_REMOVE(&tile->head_egg, egg, entries);
        egg = TAILQ_NEXT(egg, entries);
    }
}

void cmd_eject(server_t *server, char *args, client_socket_t *client)
{
    int x = client->player->pos.x;
    int y = client->player->pos.y;
    bool pushed = false;

    pushed = player_eject(server, client->player);
    check_all_egg(server->grid->tiles[x][y], server);
    if (pushed == true) {
        dprintf(client->socket, "ok\n");
    } else
        dprintf(client->socket, "ko\n");
}

void cmd_take(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int result = player_take_item(player,
    server->grid->tiles[player->pos.y][player->pos.x], parse_args[1]);

    if (result >= 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    if (!get_gui(server))
        return;
    bct(server, player->pos);
    dprintf(get_gui(server)->socket, "pgt %d %d\n", client->id, result);
}

void cmd_set(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int result = player_drop_item(player,
    server->grid->tiles[player->pos.y][player->pos.x], parse_args[1]);

    if (result >= 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    if (!get_gui(server))
        return;
    bct(server, player->pos);
    dprintf(get_gui(server)->socket, "pdr %d %d\n", client->id, result);
}
