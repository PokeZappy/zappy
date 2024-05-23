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

    team->_name = strdup(name);
    team->_max_clients = max_clients;
    team->_current_clients = 0;
    return team;
}

void free_team(team_t *team)
{
    free(team->_name);
    free(team);
}
