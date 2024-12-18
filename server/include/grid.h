/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** grid.h
*/

#pragma once

#include "tile.h"

typedef struct grid_s {
    int width; // size of the grid
    int height; // size of the grid
    tiles_t ***tiles; // 2D array of tiles
} grid_t;

grid_t *init_grid(server_t *server, int width, int height);
void free_grid(grid_t *grid);
double *create_density(int tile_nbr);
void generate_resource(server_t *server, grid_t *grid);
