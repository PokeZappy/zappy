/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_gui3.c
*/

#include "../../../include/commands.h"

void bct(server_t *server, vector_t pos)
{
    tiles_t *tile = server->grid->tiles[pos.y][pos.x];
    char *response = get_tile_content(tile);

    if (!get_gui(server))
        return;
    dprintf(get_gui(server)->socket, "bct %d %d %s\n", pos.x, pos.y,
    response);
    free(response);
}

void cmd_sgt(server_t *server, char *args, client_socket_t *client)
{
    dprintf(client->socket, "sgt %d\n", server->arguments->f);
}

void cmd_sst(server_t *server, char *args, client_socket_t *client)
{
    int new_f = atoi(args + 4);

    server->arguments->f = new_f;
    dprintf(get_gui(server)->socket, "sst %d\n", new_f);
}
