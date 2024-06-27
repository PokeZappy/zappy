/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_grid.c
*/

#include "../../include/grid.h"
#include "../../include/server.h"
#include "stdlib.h"
#include "stdio.h"

static int count_resource_on_map(grid_t *grid, int resource_type)
{
    int count = 0;

    for (int i = 0; i < grid->height; i++)
        for (int j = 0; j < grid->width; j++)
            count += grid->tiles[i][j]->items[resource_type];
    return count;
}

static void spawn_resource(server_t *server, grid_t *grid, int resource_type)
{
    int x = rand() % grid->width;
    int y = rand() % grid->height;

    grid->tiles[y][x]->items[resource_type] += 1;
    if (!server)
        bct(server, (vector_t){x, y});
}

void generate_resource(server_t *server, grid_t *grid)
{
    int case_nbr = grid->width * grid->height;
    double *densities = create_density(case_nbr);
    double resource_count;

    for (int type = 0; type < ITEM_PER_TILE; type++) {
        resource_count = densities[type];
        resource_count -= count_resource_on_map(grid, type);
        for (int i = 0; i < resource_count; i++)
            spawn_resource(server, grid, type);
    }
    free(densities);
}

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

    grid->width = width;
    grid->height = height;
    grid->tiles = (tiles_t ***)malloc(sizeof(tiles_t **) * height);
    for (int i = 0; i < height; i++) {
        grid->tiles[i] = (tiles_t **)malloc(sizeof(tiles_t *) * width);
        for (int j = 0; j < width; j++)
            grid->tiles[i][j] =
                    init_tile();
    }
    generate_resource(server, grid);
    return grid;
}

void free_grid(grid_t *grid)
{
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++)
            free_tile(grid->tiles[i][j]);
        free(grid->tiles[i]);
    }
    free(grid->tiles);
    free(grid);
}
