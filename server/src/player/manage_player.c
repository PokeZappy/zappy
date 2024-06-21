/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_player.c
*/

#include "../../include/player.h"
#include <stdlib.h>
#include <time.h>

static int generate_player_id(void)
{
    static int id = 0;

    id++;
    return id;
}

static egg_t *check_egg_name(tiles_t *tile, char *team_name)
{
    egg_t *e = TAILQ_FIRST(&tile->_head_egg);

    while (e != NULL) {
        if (strcmp(e->_team->_name, team_name) == 0 && e->_available == 0) {
            TAILQ_REMOVE(&tile->_head_egg, e, _entries);
            return e;
        }
        e = TAILQ_NEXT(e, _entries);
    }
    return NULL;
}

static egg_t *loop_tile(server_t *server, char *team_name, int i)
{
    tiles_t ***tiles = server->grid->_tiles;
    int y = server->grid->_width;
    egg_t *tmp = NULL;

    for (int j = 0; j < y; j++) {
        tmp = check_egg_name(tiles[i][j], team_name);
        if (tmp != NULL)
            return tmp;
    }
    return tmp;
}

static egg_t *check_for_egg(server_t *server, char *team_name)
{
    tiles_t ***tiles = server->grid->_tiles;
    int x = server->grid->_height;
    int y = server->grid->_width;
    egg_t *tmp = NULL;

    for (int i = 0; i < x; i++) {
        tmp = loop_tile(server, team_name, i);
        if (tmp != NULL)
            return tmp;
    }
    return tmp;
}

static void remove_egg(server_t *server, egg_t *egg)
{
    TAILQ_REMOVE(&server->grid->_tiles[egg->_pos._x][egg->_pos._y]->_head_egg,
        egg, _entries);
    TAILQ_REMOVE(&server->_head_egg, egg, _entries);
}

static void check_for_pos(player_t *player, server_t *server)
{
    int w = server->grid->_width;
    int h = server->grid->_height;
    egg_t *rand_egg = check_for_egg(server, player->_team->_name);

    if (rand_egg == NULL) {
        player->_pos._x = rand() % w;
        player->_pos._y = rand() % h;
    } else {
        player->_pos._x = rand_egg->_pos._x;
        player->_pos._y = rand_egg->_pos._y;
        dprintf(get_gui(server)->socket, "ebo %d\n", rand_egg->_id);
        remove_egg(server, rand_egg);
    }
}

player_t *init_player(team_t *team, server_t *server)
{
    player_t *player = (player_t *)malloc(sizeof(player_t));

    if (team->_current_clients >= team->_max_clients) {
        free(player);
        return (NULL);
    }
    player->_id = generate_player_id();
    player->_level = 1;
    player->_direction = (direction_t)(rand() % 4);
    for (int i = 0; i < ITEM_PER_TILE; i++)
        player->_inventory[i] = 0;
    player->_inventory[0] = 9;
    player->_health = 126;
    player->_team = team;
    team->_current_clients++;
    check_for_pos(player, server);
    return player;
}

player_t *add_player_to_team(char *team_name, server_t *server)
{
    team_t *team = search_team(team_name, server);

    if (team == NULL)
        return NULL;
    return init_player(team, server);
}

void free_player(player_t *player)
{
    free(player);
}
