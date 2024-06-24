/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** team.h
*/

#pragma once

#include <sys/queue.h>
#include "player.h"
#include "server.h"

typedef struct team_s {
    char *name; // name of the team
    int max_clients; // max number of clients
    int current_clients; // current number of clients
    TAILQ_ENTRY(team_s) entries; // list of teams
} team_t;

team_t *init_team(char *name, int max_clients);
team_t *search_team(char *team_name, struct server_s *server);
void free_team(team_t *team);
int get_client_rest(team_t *team);
