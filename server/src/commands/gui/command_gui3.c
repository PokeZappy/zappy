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

    dprintf(get_gui(server)->socket, "bct %d %d %s\n", pos.x, pos.y,
    response);
    free(response);
}
