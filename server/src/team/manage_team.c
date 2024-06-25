/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_team.c
*/

#include "../../include/team.h"
#include <stdlib.h>
#include <string.h>

team_t *init_team(char *name, int max_clients)
{
    team_t *team = (team_t *)malloc(sizeof(team_t));

    team->name = strdup(name);
    team->max_clients = max_clients;
    team->current_clients = 0;
    return team;
}

void free_team(team_t *team)
{
    free(team->name);
    free(team);
}

team_t *search_team(char *team_name, server_t *server)
{
    team_t *team = TAILQ_FIRST(&server->head_team);

    while (team != NULL) {
        if (strcmp(team->name, team_name) == 0)
            return team;
        team = TAILQ_NEXT(team, entries);
    }
    return NULL;
}

int get_client_rest(team_t *team)
{
    return team->max_clients - team->current_clients;
}
