/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** objects.h
*/

#pragma once

#include "direction.h"
#include "vector.h"
#include "constant.h"
#include "team.h"

typedef struct player_s {
    vector_t _pos; // position of the player
    direction_t _direction; // looking direction of the player
    int _level; // level of the player
    int _items[ITEM_PER_TILE]; // list items on the tile
    struct team_s *_team; // team of the player
    TAILQ_ENTRY(player_s) _entries; // list of players
} player_t;

player_t *init_player(void);
void free_player(player_t *player);
void add_item_to_player(player_t *player, int item);
void remove_item_from_player(player_t *player, int item, int quantity);
int get_player_level(player_t *player);
int increment_player_level(player_t *player);
