/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_grid.c
*/

#include "../../../include/tile.h"

void add_item_to_tile(tiles_t *tile, int item, int quantity)
{
    tile->_items[item] += quantity;
}

void remove_item_from_tile(tiles_t *tile, int item, int quantity)
{
    tile->_items[item] -= quantity;
}
