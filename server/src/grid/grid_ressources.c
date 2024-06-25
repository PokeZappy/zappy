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

int count_resource_on_map(grid_t *grid, int resource_type)
{
    int count = 0;

    for (int i = 0; i < grid->height; i++)
        for (int j = 0; j < grid->width; j++)
            count += grid->tiles[i][j]->items[resource_type];
    return count;
}

void spawn_resource(server_t *server, grid_t *grid, int resource_type)
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
