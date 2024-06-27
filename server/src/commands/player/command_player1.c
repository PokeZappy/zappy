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
    player_move(client->player, server->grid->width, server->grid->height);
    dprintf(client->socket, "ok\n");
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "ppo %d %d %d %d\n", client->id,
        client->player->pos.x, client->player->pos.y,
        client->player->direction + 1);
}

void cmd_right(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !client->player)
        return;
    player_orientation(client->player, 1);
    dprintf(client->socket, "ok\n");
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "ppo %d %d %d %d\n", client->id,
        client->player->pos.x, client->player->pos.y,
        client->player->direction + 1);
}

void cmd_left(server_t *server, char *args, client_socket_t *client)
{
    if (!client || !client->player)
        return;
    player_orientation(client->player, 0);
    dprintf(client->socket, "ok\n");
    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "ppo %d %d %d %d\n", client->id,
        client->player->pos.x, client->player->pos.y,
        client->player->direction + 1);
}

void cmd_look(server_t *server, char *args, client_socket_t *client)
{
    char *response;

    if (!client || !client->player)
        return;
    response = player_look(server, client->player);
    print_buffer(client->socket, response);
    free(response);
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
    dprintf(get_gui(server)->socket, "pin %d %d %d %s\n", client->id,
        client->player->pos.x, client->player->pos.y, response);
    free(response);
}
