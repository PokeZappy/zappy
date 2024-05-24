/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_tile.c
*/

#include "../../../include/tile.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"

tiles_t *init_tile(void)
{
    tiles_t *tile = (tiles_t *)malloc(sizeof(tiles_t));
    double random_number;
    double densities[ITEM_PER_TILE] = {DENSITY_FOOD, DENSITY_LINEMATE,
    DENSITY_DERAUMERE, DENSITY_SIBUR, DENSITY_MENDIANE, DENSITY_PHIRAS,
    DENSITY_THYSTAME};

    srand(time(NULL));
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        random_number = rand() % 100;
        tile->_items[i] = random_number <= (densities[i] * 100) ? 1 : 0;
    }
    return tile;
}

void free_tile(tiles_t *tile)
{
    free(tile);
}
