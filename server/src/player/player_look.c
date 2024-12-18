/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** player_look.c
*/

#include "../../include/server.h"
#include "../../include/objects.h"

static vector_t get_looked_tile(grid_t *grid, vector_t pos)
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

static vector_t find_tile(grid_t *grid, player_t *player, int i, int j)
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

static void print_nb_looked_players(char *result, int nb)
{
    if (nb == 0)
        return;
    for (int i = 0; i < nb; i++) {
        sprintf(result, "%s player", result);
    }
}

static void print_lookeditems_on_tile(char *result, tiles_t *tile)
{
    for (int i = 0; i < ITEM_PER_TILE; i++) {
        if (tile->items[i] == 0)
            continue;
        for (int j = 0; j < tile->items[i]; j++)
            sprintf(result, "%s %s", result, object_names[i]);
    }
}

static void player_look_loop(server_t *server, player_t *p, int i, char *r)
{
    vector_t current;
    int nb = 0;

    for (int j = i; j >= (0 - i); j--) {
        current = find_tile(server->grid, p, i, j);
        nb = nb_player_on_tile(server, current);
        print_nb_looked_players(r, nb);
        print_lookeditems_on_tile(r,
        server->grid->tiles[current.y][current.x]);
        if (j == (0 - i) && i == p->level) {
            sprintf(r, "%s", r);
            break;
        }
        sprintf(r, "%s,", r);
    }
}

char *player_look(server_t *server, player_t *player)
{
    char *result = (char *)malloc(sizeof(char) * 16384);

    sprintf(result, "[");
    for (int i = 0; i <= player->level; i++) {
        player_look_loop(server, player, i, result);
    }
    sprintf(result, "%s ]\n", result);
    return result;
}
