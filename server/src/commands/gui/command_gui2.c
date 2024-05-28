/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_gui2.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_ppo(server_t *server, char *args, client_socket_t *client)
{
    char **parse_command = decompose_output(args);
    int player_nbr = atoi(parse_command[1]);
    player_t *player = find_player_by_socket(server, player_nbr);

    if (!client || !is_client_gui(client) || !player)
        return;
    dprintf(client->socket, "ppo %d %d %d %d\n", player->_id, player->_pos._x,
    player->_pos._y, player->_direction + 1);
    printf("ppo\n");
}

void cmd_plv(server_t *server, char *args, client_socket_t *client)
{
    char **parse_command = decompose_output(args);
    int player_nbr = atoi(parse_command[1]);
    player_t *player = find_player_by_socket(server, player_nbr);

    if (!client || !is_client_gui(client) || !player)
        return;
    dprintf(client->socket, "plv %d %d\n", player->_id, player->_level);
    printf("plv\n");
}

void cmd_pin(server_t *server, char *args, client_socket_t *client)
{
    char **parse_command = decompose_output(args);
    int player_nbr = atoi(parse_command[1]);
    player_t *player = find_player_by_socket(server, player_nbr);
    char *response;

    if (!client || !is_client_gui(client) || !player)
        return;
    response = get_player_inventory(player);
    dprintf(client->socket, "pin %d %d %d %s\n", player->_id,
    player->_pos._x, player->_pos._y, response);
    free(response);
    printf("pin\n");
}

void cmd_pex(server_t *server, char *args, client_socket_t *client)
{
    printf("pex\n");
}
