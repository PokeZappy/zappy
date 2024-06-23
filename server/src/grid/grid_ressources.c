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

    for (int i = 0; i < grid->_height; i++)
        for (int j = 0; j < grid->_width; j++)
            count += grid->_tiles[i][j]->_items[resource_type];
    return count;
}

void spawn_resource(server_t *server, grid_t *grid, int resource_type)
{
    int x = rand() % grid->_width;
    int y = rand() % grid->_height;

    grid->_tiles[y][x]->_items[resource_type] += 1;
    if (get_gui(server)) {
        dprintf(get_gui(server)->socket, "bct %d %d %d %d %d %d %d %d %d\n",
        x, y, grid->_tiles[y][x]->_items[0],
        grid->_tiles[y][x]->_items[1], grid->_tiles[y][x]->_items[2],
        grid->_tiles[y][x]->_items[3], grid->_tiles[y][x]->_items[4],
        grid->_tiles[y][x]->_items[5], grid->_tiles[y][x]->_items[6]);
    }
}

void generate_resource(server_t *server, grid_t *grid)
{
    int case_nbr = grid->_width * grid->_height;
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
