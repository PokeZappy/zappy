/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** grid.h
*/

#pragma once

#include "tile.h"

typedef struct grid_s {
    int _width; // size of the grid
    int _height; // size of the grid
    tiles_t **_tiles; // 2D array of tiles
} grid_t;

grid_t *init_grid(int width, int height);
void free_grid(grid_t *grid);
