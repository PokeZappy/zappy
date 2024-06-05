/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** tiles.h
*/

#pragma once

#include "constant.h"

typedef struct tiles_s {
    int _items[ITEM_PER_TILE]; // list items on the tile
} tiles_t;

tiles_t *init_tile(double *density, int case_nbr, int current_case);
void free_tile(tiles_t *tile);
void add_item_to_tile(tiles_t *tile, int item, int quantity);
void remove_item_from_tile(tiles_t *tile, int item, int quantity);
int get_item_count(tiles_t *tile, int item);
char *get_tile_content(tiles_t *tile);
