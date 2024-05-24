/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_grid.c
*/

#include "../../include/grid.h"
#include "stdlib.h"


grid_t *init_grid(int width, int height)
{
    grid_t *grid = (grid_t *)malloc(sizeof(grid_t));

    grid->_width = width;
    grid->_height = height;
    grid->_tiles = (tiles_t **)malloc(sizeof(tiles_t *) * height);
    for (int i = 0; i < height; i++) {
        grid->_tiles[i] = (tiles_t *)malloc(sizeof(tiles_t) * width);
        for (int j = 0; j < width; j++)
            grid->_tiles[i][j] = *(tiles_t *)init_tile();
    }
    return grid;
}

void free_grid(grid_t *grid)
{
    for (int i = 0; i < grid->_height; i++) {
        for (int j = 0; j < grid->_width; j++) {
            free_tile(&grid->_tiles[i][j]);
        }
        free(grid->_tiles[i]);
    }
    free(grid->_tiles);
    free(grid);
}
