/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player2.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_eject(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    int x = player->_pos._x;
    int y = player->_pos._y;
    bool pushed = false;

    if (!player)
        return;
    pushed = player_eject(server, player);
    if (pushed == true) {
        free_all_egg(server->grid->_tiles[x][y]);
        dprintf(client->socket, "ok\n");
    } else
        dprintf(client->socket, "ko\n");
    dprintf(get_gui(server)->socket, "pex #%d\n", client->_id);
    printf("eject\n");
}

void cmd_take(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int obj_taken = atoi(parse_args[1]);
    int result;

    if (!player) {
        free_str_array(parse_args);
        return;
    }
    result = player_take_item(player,
    server->grid->_tiles[player->_pos._y][player->_pos._y], obj_taken);
    if (result == 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    dprintf(get_gui(server)->socket, "pgt #%d %d\n", client->_id, obj_taken);
    printf("take\n");
}

void cmd_set(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int obj_set = atoi(parse_args[1]);
    int result;

    if (!player) {
        free_str_array(parse_args);
        return;
    }
    result = player_take_item(player,
    server->grid->_tiles[player->_pos._y][player->_pos._y], obj_set);
    if (result == 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    dprintf(get_gui(server)->socket, "pdr #%d %d\n", client->_id, obj_set);
    printf("set\n");
}
