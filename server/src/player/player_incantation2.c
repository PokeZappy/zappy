/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/incantation.h"
#include "../../include/server.h"

bool player_is_participant(cmd_incantation_t *cu, client_socket_t *cl)
{
    for (int i = 0; i < cu->number_of_participants; i++) {
        if (cu->participants[i] == cl)
            return true;
    }
    return false;
}

cmd_incantation_t *find_incantation(server_t *s, client_socket_t *c)
{
    cmd_incantation_t *current = TAILQ_FIRST(&s->head_incantation);

    while (current) {
        if (current->organizer == c)
            return current;
        if (player_is_participant(current, c))
            return current;
        current = TAILQ_NEXT(current, entries);
    }
    return NULL;
}

bool player_still_onpos(cmd_incantation_t *current)
{
    client_socket_t *cli;

    for (int i = 0; i < current->number_of_participants; i++) {
        if (!current->participants[i])
            return false;
        cli = current->participants[i];
        if (cli->player->pos.x != current->tile_vector.x ||
        cli->player->pos.y != current->tile_vector.y)
            return false;
    }
    return true;
}

void free_incantation(server_t *server, cmd_incantation_t *current)
{
    TAILQ_REMOVE(&server->head_incantation, current, entries);
    free(current->participants);
    free(current);
}

bool check_post_incantation(server_t *server, client_socket_t *client)
{
    cmd_incantation_t *current = find_incantation(server, client);
    incantation_t incantation = incantations[client->player->level - 1];
    tiles_t *tile = server->grid->tiles[current->tile_vector.y]
    [current->tile_vector.x];

    if (!player_still_onpos(current))
        return false;
    for (int i = 0; i < 7; i++) {
        if (tile->items[i] < incantation.objects_required[i])
            return false;
        tile->items[i] -= incantation.objects_required[i];
    }
    return true;
}
