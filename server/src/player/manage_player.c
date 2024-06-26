/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_player.c
*/

#include "../../include/player.h"
#include <stdlib.h>
#include <time.h>

static int generate_playerid(void)
{
    static int id = 0;

    id++;
    return id;
}

static egg_t *check_for_egg(server_t *server, char *team_name)
{
    egg_t *tmp = TAILQ_FIRST(&server->head_egg);

    TAILQ_FOREACH(tmp, &server->head_egg, entries) {
        if (strcmp(tmp->team->name, team_name) == 0)
            return tmp;
        tmp = TAILQ_NEXT(tmp, entries);
    }
    return NULL;
}

static void remove_egg(server_t *server, egg_t *egg)
{
    TAILQ_REMOVE(&server->grid->tiles[egg->pos.x][egg->pos.y]->head_egg,
        egg, entries);
    TAILQ_REMOVE(&server->head_egg, egg, entries);
}

static void check_forpos(player_t *player, server_t *server)
{
    int w = server->grid->width;
    int h = server->grid->height;
    egg_t *rand_egg = check_for_egg(server, player->team->name);

    if (rand_egg == NULL) {
        player->pos.x = rand() % w;
        player->pos.y = rand() % h;
    } else {
        player->pos.x = rand_egg->pos.x;
        player->pos.y = rand_egg->pos.y;
        if (get_gui(server))
            dprintf(get_gui(server)->socket, "ebo %d\n", rand_egg->id);
        remove_egg(server, rand_egg);
    }
}

player_t *init_player(team_t *team, server_t *server)
{
    player_t *player = (player_t *)malloc(sizeof(player_t));

    if (team->current_clients >= team->max_clients) {
        free(player);
        return (NULL);
    }
    player->id = generate_playerid();
    player->level = 1;
    player->direction = (direction_t)(rand() % 4);
    for (int i = 0; i < ITEM_PER_TILE; i++)
        player->inventory[i] = 0;
    player->inventory[0] = 9;
    player->health = 126000;
    player->team = team;
    team->current_clients++;
    check_forpos(player, server);
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
