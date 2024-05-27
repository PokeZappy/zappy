/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** objects.h
*/

#pragma once

#include <stdbool.h>
#include "direction.h"
#include "vector.h"
#include "constant.h"
#include "team.h"
#include "server.h"
#include "grid.h"
#include "list.h"

typedef struct player_s {
    int _id; // id of the player
    int _fd; // file descriptor of the player
    vector_t _pos; // position of the player
    direction_t _direction; // looking direction of the player
    int _level; // level of the player
    int _inventory[ITEM_PER_TILE]; // list items on the tile
    struct team_s *_team; // team of the player
    TAILQ_ENTRY(player_s) _entries; // list of players
} player_t;

// -- PLAYER RELATED -- //
player_t *init_player(struct team_s *team, int width, int height);
void free_player(player_t *player);
void add_item_to_player(player_t *player, int item, int quantity);
void remove_item_from_player(player_t *player, int item, int quantity);
int get_player_level(player_t *player);
int increment_player_level(player_t *player);
void player_move(player_t *player, int map_width, int map_height);
void player_orientation(player_t *player, bool right);
char *print_player_inventory(player_t *player);
char *get_player_inventory(player_t *player);

// -- SERVER RELATED -- //
player_t *add_player_to_team(char *team_name, struct server_s *server);
list_t *get_player_on_tile(struct server_s *server, vector_t pos);

// -- GRID RELATED -- //
bool player_take_item(player_t *player, tiles_t *tile, int item);
bool player_drop_item(player_t *player, tiles_t *tile, int item);
