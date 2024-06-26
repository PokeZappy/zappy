/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** tiles.h
*/

#pragma once

#include <sys/queue.h>

#include "constant.h"
#include "egg.h"

typedef struct tiles_s {
    int items[ITEM_PER_TILE]; // list items on the tile
    TAILQ_HEAD(, egg_s) head_egg; // list of egg
} tiles_t;

tiles_t *init_tile(void);
void free_tile(tiles_t *tile);
void free_all_egg(tiles_t *tile);
void add_item_to_tile(tiles_t *tile, int item, int quantity);
void remove_item_from_tile(tiles_t *tile, int item, int quantity);
char *get_tile_content(tiles_t *tile);
