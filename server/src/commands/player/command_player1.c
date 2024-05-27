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
    printf("forward\n");
}

void cmd_right(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !client->player)
        return;
    player_orientation(client->player, 1);
    dprintf(client->socket, "ok\n");
    printf("right\n");
}

void cmd_left(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !client->player)
        return;
    player_orientation(client->player, 0);
    dprintf(client->socket, "ok\n");
    printf("left\n");
}

void cmd_look(server_t *server, char *args, client_socket_t *client)
{
    printf("look\n");
}

void cmd_inventory(server_t *server, char *args, client_socket_t *client)
{
    char *response;

    if (!client || !client->player)
        return;
    response = print_player_inventory(client->player);
    dprintf(client->socket, "%s\n", response);
    free(response);
    printf("inventory\n");
}
