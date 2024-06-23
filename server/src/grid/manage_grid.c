/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_grid.c
*/

#include "../../include/grid.h"
#include "stdlib.h"
#include "stdio.h"

double *create_density(int tile_nbr)
{
    double *densities = (double *)malloc(ITEM_PER_TILE * sizeof(double));

    if (densities == NULL)
        return NULL;
    densities[0] = DENSITY_FOOD * tile_nbr;
    densities[1] = DENSITY_LINEMATE * tile_nbr;
    densities[2] = DENSITY_DERAUMERE * tile_nbr;
    densities[3] = DENSITY_SIBUR * tile_nbr;
    densities[4] = DENSITY_MENDIANE * tile_nbr;
    densities[5] = DENSITY_PHIRAS * tile_nbr;
    densities[6] = DENSITY_THYSTAME * tile_nbr;
    return densities;
}

grid_t *init_grid(server_t *server, int width, int height)
{
    grid_t *grid = (grid_t *)malloc(sizeof(grid_t));

    grid->_width = width;
    grid->_height = height;
    grid->_tiles = (tiles_t ***)malloc(sizeof(tiles_t **) * height);
    for (int i = 0; i < height; i++) {
        grid->_tiles[i] = (tiles_t **)malloc(sizeof(tiles_t *) * width);
        for (int j = 0; j < width; j++)
            grid->_tiles[i][j] =
                init_tile();
    }
    generate_resource(server, grid);
    return grid;
}

void print_tile(tiles_t *tile)
{
    for (int i = 0; i < ITEM_PER_TILE; i++)
        printf("%d ", tile->_items[i]);
    printf("\n");
}

void print_grid(grid_t *grid)
{
    for (int i = 0; i < grid->_height; i++) {
        for (int j = 0; j < grid->_width; j++)
            print_tile(grid->_tiles[i][j]);
        printf("\n");
    }
}

void free_grid(grid_t *grid)
{
    for (int i = 0; i < grid->_height; i++) {
        for (int j = 0; j < grid->_width; j++)
            free_tile(grid->_tiles[i][j]);
        free(grid->_tiles[i]);
    }
    free(grid->_tiles);
    free(grid);
}
