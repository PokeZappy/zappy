/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_player1.c
*/

#include "../../../include/commands.h"

void cmd_forward(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !client->player)
        return;
    player_move(client->player, server->grid->_width, server->grid->_height);
    dprintf(client->socket, "ok\n");
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "ppo %d %d %d %d\n", client->_id,
        client->player->_pos._x, client->player->_pos._y,
        client->player->_direction + 1);
    printf("forward\n");
}

void cmd_right(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !client->player)
        return;
    player_orientation(client->player, 1);
    dprintf(client->socket, "ok\n");
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "ppo %d %d %d %d\n", client->_id,
        client->player->_pos._x, client->player->_pos._y,
        client->player->_direction + 1);
    printf("right\n");
}

void cmd_left(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !client->player)
        return;
    player_orientation(client->player, 0);
    dprintf(client->socket, "ok\n");
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "ppo %d %d %d %d\n", client->_id,
        client->player->_pos._x, client->player->_pos._y,
        client->player->_direction + 1);
    printf("left\n");
}

void cmd_look(server_t *server, char *args, client_socket_t *client)
{
    char *response;

    if (!client || !client->player)
        return;
    response = player_look(server, client->player);
    dprintf(client->socket, "%s\n", response);
    free(response);
    printf("look\n");
}

void cmd_inventory(server_t *server, char *args, client_socket_t *client)
{
    char *response;

    if (!client || !client->player)
        return;
    response = print_player_inventory(client->player);
    dprintf(client->socket, "%s\n", response);
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "pin %d %d %d %s\n", client->_id,
        client->player->_pos._x, client->player->_pos._y, response);
    free(response);
    printf("inventory\n");
}
