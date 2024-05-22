/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** team.h
*/

#pragma once

#include <sys/queue.h>

#include "player.h"

typedef struct team_s {
    char *_name; // name of the team
    int _max_clients; // max number of clients
    int _current_clients; // current number of clients
    TAILQ_HEAD(, player_t) _players; // list of players
    TAILQ_ENTRY(team_s) entries; // list of teams
} team_t;

team_t *init_team(char *name, int max_clients);
void free_team(team_t *team);
void add_player_to_team(team_t *team, player_t *player);
