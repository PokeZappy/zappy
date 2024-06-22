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
    if (pos._x < 0)
        pos._x = grid->_width + pos._x;
    if (pos._y < 0)
        pos._y = grid->_height + pos._y;
    if (pos._x >= grid->_width)
        pos._x = pos._x - grid->_width;
    if (pos._y >= grid->_height)
        pos._y = pos._y - grid->_height;
    return pos;
}

vector_t find_tile(grid_t *grid, player_t *player, int i, int j)
{
    vector_t pos = {player->_pos._x, player->_pos._y};

    if (player->_direction == UP)
        pos = (vector_t){pos._x += j, pos._y -= i};
    if (player->_direction == RIGHT)
        pos = (vector_t){pos._x += i, pos._y += j};
    if (player->_direction == DOWN)
        pos = (vector_t){pos._x -= j, pos._y += i};
    if (player->_direction == LEFT)
        pos = (vector_t){pos._x -= i, pos._y -= j};
    return get_looked_tile(grid, pos);
}

void print_nb_looked_players(char *result, int nb)
{
    if (nb == 0)
        return;
    if (result[strlen(result) - 1] == '[')
        sprintf(result, "%splayer", result);
    else
        sprintf(result, "%s player", result);
}

void print_looked_items_on_tile(char *result, tiles_t *tile)
{
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if (tile->_items[i] != 0)
            sprintf(result, "%s %s", result, object_names[i]);
    }
}

void player_look_loop(server_t *server, player_t *p, int i, char *result)
{
    vector_t current;
    int nb = 0;

    for (int j = (0 - i); j <= i; j++) {
        current = find_tile(server->grid, p, i, j);
        nb = nb_player_on_tile(server, current);
        print_nb_looked_players(result, nb);
        print_looked_items_on_tile(result,
        server->grid->_tiles[current._y][current._x]);
        if (j == i && i == p->_level) {
            sprintf(result, "%s", result);
            break;
        }
        sprintf(result, "%s,", result);
    }
}
