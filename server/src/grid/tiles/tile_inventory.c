/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_grid.c
*/

#include "../../../include/tile.h"
#include "stdlib.h"
#include "stdio.h"

void add_item_to_tile(tiles_t *tile, int item, int quantity)
{
    tile->items[item] += quantity;
}

void remove_item_from_tile(tiles_t *tile, int item, int quantity)
{
    tile->items[item] -= quantity;
}

char *get_tile_content(tiles_t *tile)
{
    char *content = (char *)malloc(sizeof(char) * 1024);

    sprintf(content, "%d %d %d %d %d %d %d", tile->items[0],
        tile->items[1], tile->items[2], tile->items[3], tile->items[4],
        tile->items[5], tile->items[6]);
    return content;
}
