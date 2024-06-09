/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_tile.c
*/

#include "../../../include/tile.h"
#include "stdlib.h"

tiles_t *init_tile(void)
{
    tiles_t *tile = (tiles_t *)malloc(sizeof(tiles_t));

    tile->_items[0] = 0;
    tile->_items[1] = 0;
    tile->_items[2] = 0;
    tile->_items[3] = 0;
    tile->_items[4] = 0;
    tile->_items[5] = 0;
    tile->_items[6] = 0;
    return tile;
}

void free_tile(tiles_t *tile)
{
    free(tile);
}
