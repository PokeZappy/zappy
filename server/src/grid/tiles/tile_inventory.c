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
    tile->_items[item] += quantity;
}

void remove_item_from_tile(tiles_t *tile, int item, int quantity)
{
    tile->_items[item] -= quantity;
}

int get_item_count(tiles_t *tile, int item)
{
    return tile->_items[item];
}

char *get_tile_content(tiles_t *tile)
{
    char *content = (char *)malloc(sizeof(char) * 1024);

    sprintf(content, "%d %d %d %d %d %d %d", tile->_items[0],
        tile->_items[1], tile->_items[2], tile->_items[3], tile->_items[4],
        tile->_items[5], tile->_items[6]);
    return content;
}
