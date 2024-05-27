/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player2.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_broadcast(server_t *server, char *args, client_socket_t *client)
{
    printf("broadcast\n");
}

void cmd_eject(server_t *server, char *args, client_socket_t *client)
{
    printf("eject\n");
}

void cmd_take(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int object_taken = atoi(parse_args[1]);
    int result;

    if (!player) {
        free_str_array(parse_args);
        return;
    }
    result = player_take_item(player,
    server->grid->_tiles[player->_pos._y][player->_pos._y] , object_taken);
    if (result == 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    printf("take\n");
}

void cmd_set(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    char **parse_args = decompose_output(args);
    int object_set = atoi(parse_args[1]);
    int result;

    if (!player) {
        free_str_array(parse_args);
        return;
    }
    result = player_take_item(player,
    server->grid->_tiles[player->_pos._y][player->_pos._y] , object_set);
    if (result == 0)
        dprintf(client->socket, "ok\n");
    else
        dprintf(client->socket, "ko\n");
    free_str_array(parse_args);
    printf("set\n");
}

void cmd_incantation(server_t *server, char *args, client_socket_t *client)
{
    printf("incantation\n");
}
