/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** egg.h
*/

#pragma once

#include "vector.h"

struct team_s;
typedef struct team_s team_t;

struct server_s;
typedef struct server_s server_t;

typedef struct egg_s {
    team_t *_team;
    int _available;
    vector_t _pos;
    int _id;
    int _client_id;
    TAILQ_ENTRY(egg_s) _entries;
} egg_t;

// -- EGG -- //
void check_eggs(server_t *server);
