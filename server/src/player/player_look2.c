/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_look.c
*/

#include "../../include/server.h"
#include "../../include/objects.h"

vector_t get_looked_tile(grid_t *grid, vector_t pos)
{
    if (pos.x < 0)
        pos.x = grid->width + pos.x;
    if (pos.y < 0)
        pos.y = grid->height + pos.y;
    if (pos.x >= grid->width)
        pos.x = pos.x - grid->width;
    if (pos.y >= grid->height)
        pos.y = pos.y - grid->height;
    return pos;
}

vector_t find_tile(grid_t *grid, player_t *player, int i, int j)
{
    vector_t pos = {player->pos.x, player->pos.y};

    if (player->direction == UP)
        pos = (vector_t){pos.x += j, pos.y -= i};
    if (player->direction == RIGHT)
        pos = (vector_t){pos.x += i, pos.y += j};
    if (player->direction == DOWN)
        pos = (vector_t){pos.x -= j, pos.y += i};
    if (player->direction == LEFT)
        pos = (vector_t){pos.x -= i, pos.y -= j};
    return get_looked_tile(grid, pos);
}

void print_nb_looked_players(char *result, int nb)
{
    if (nb == 0)
        return;
    if (result[strlen(result) - 1] == '[')
        sprintf(result, "%splayer", result);
    else
        sprintf(result, "%splayer", result);
}

void print_lookeditems_on_tile(char *result, tiles_t *tile)
{
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if (tile->items[i] != 0)
            sprintf(result, "%s %s", result, object_names[i]);
    }
}

void player_look_loop(server_t *server, player_t *p, int i, char *result)
{
    vector_t current;
    int nb = 0;

    for (int j = i; j >= (0 - i); j--) {
        current = find_tile(server->grid, p, i, j);
        nb = nb_player_on_tile(server, current);
        print_nb_looked_players(result, nb);
        print_lookeditems_on_tile(result,
        server->grid->tiles[current.y][current.x]);
        if (j == (0 - i) && i == p->level) {
            sprintf(result, "%s", result);
            break;
        }
        sprintf(result, "%s,", result);
    }
}
