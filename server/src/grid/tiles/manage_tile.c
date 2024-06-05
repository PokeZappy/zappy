/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_tile.c
*/

#include "../../../include/tile.h"
#include "stdlib.h"

static int random_chance(int density, int case_nbr, int current_case)
{
    int rand_chance = 0;
    int case_left = case_nbr - current_case;

    if (case_left == density)
        return 1;
    rand_chance = rand() % 2;
    return rand_chance;
}

tiles_t *init_tile(double *density, int case_nbr, int current_case)
{
    tiles_t *tile = (tiles_t *)malloc(sizeof(tiles_t));

    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if (density[i] < 1) {
            tile->_items[i] = 0;
            continue;
        }
        if (random_chance(density[i], case_nbr, current_case)) {
            tile->_items[i] = 1;
            density[i] -= 1;
        } else {
            tile->_items[i] = 0;
        }
    }
    return tile;
}

void free_tile(tiles_t *tile)
{
    free(tile);
}
