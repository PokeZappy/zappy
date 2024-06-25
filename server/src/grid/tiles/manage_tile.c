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

    TAILQ_INIT(&tile->head_egg);
    tile->items[0] = 0;
    tile->items[1] = 0;
    tile->items[2] = 0;
    tile->items[3] = 0;
    tile->items[4] = 0;
    tile->items[5] = 0;
    tile->items[6] = 0;
    return tile;
}

void free_all_egg(tiles_t *tile)
{
    egg_t *egg = TAILQ_FIRST(&tile->head_egg);
    egg_t *tmp_egg;

    while (egg != NULL) {
        tmp_egg = TAILQ_NEXT(egg, entries);
        TAILQ_REMOVE(&tile->head_egg, egg, entries);
        free(egg);
        egg = tmp_egg;
    }
}

void free_tile(tiles_t *tile)
{
    free_all_egg(tile);
    free(tile);
}
