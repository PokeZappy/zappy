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

player_t *init_player(team_t *team)
{
    player_t *player = (player_t *)malloc(sizeof(player_t));

    if (team->_current_clients >= team->_max_clients) {
        free(player);
        return (NULL);
    }
    player->_id = generate_player_id();
    player->_level = 1;
    player->_pos = (vector_t){0, 0};
    player->_direction = UP;
    srand(time(NULL));
    player->_direction = (direction_t)(rand() % 4);
    for (int i = 0; i < ITEM_PER_TILE; i++)
        player->_inventory[i] = 0;
    player->_team = team;
    team->_current_clients++;
    return player;
}

player_t *add_player_to_team(char *team_name, server_t *server)
{
    player_t *new_player;
    team_t *team = search_team(team_name, server);

    if (team == NULL)
        return NULL;
    return init_player(team);
}

void free_player(player_t *player)
{
    free(player);
}
