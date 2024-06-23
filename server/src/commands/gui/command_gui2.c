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
    client_socket_t *cl = find_client_by_socket(server, player_nbr);

    if (!client || !is_client_gui(client) || !cl->player)
        return;
    dprintf(client->socket, "ppo %d %d %d %d\n", cl->_id, cl->player->_pos._x,
    cl->player->_pos._y, cl->player->_direction + 1);
}

void cmd_plv(server_t *server, char *args, client_socket_t *client)
{
    char **parse_command = decompose_output(args);
    int player_nbr = atoi(parse_command[1]);
    client_socket_t *cl = find_client_by_socket(server, player_nbr);

    if (!client || !is_client_gui(client) || !cl->player)
        return;
    dprintf(client->socket, "plv %d %d\n", cl->_id, cl->player->_level);
}

void cmd_pin(server_t *server, char *args, client_socket_t *client)
{
    char **parse_command = decompose_output(args);
    int player_nbr = atoi(parse_command[1]);
    client_socket_t *cl = find_client_by_socket(server, player_nbr);
    char *response;

    if (!client || !is_client_gui(client) || !cl->player)
        return;
    response = get_player_inventory(cl->player);
    dprintf(client->socket, "pin %d %d %d %s\n", cl->_id,
    cl->player->_pos._x, cl->player->_pos._y, response);
    free(response);
}
