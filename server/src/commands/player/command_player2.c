/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player2.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_broadcast(server_t *server, char *args, int client_nbr)
{
    printf("broadcast\n");
}

void cmd_eject(server_t *server, char *args, int client_nbr)
{
    printf("eject\n");
}

void cmd_take(server_t *server, char *args, int client_nbr)
{
    player_t *player = find_player_by_socket(server, client_nbr);
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
        dprintf(client_nbr, "ok\n");
    else
        dprintf(client_nbr, "ko\n");
    free_str_array(parse_args);
    printf("take\n");
}

void cmd_set(server_t *server, char *args, int client_nbr)
{
    player_t *player = find_player_by_socket(server, client_nbr);
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
        dprintf(client_nbr, "ok\n");
    else
        dprintf(client_nbr, "ko\n");
    free_str_array(parse_args);
    printf("set\n");
}

void cmd_incantation(server_t *server, char *args, int client_nbr)
{
    printf("incantation\n");
}
