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
    for (int i = 0; cu->participants[i] != NULL; i++) {
        if (cu->participants[i] == cl)
            return true;
    }
    return false;
}

cmd_incantation_t *find_correct_incantation(server_t *s, client_socket_t *c)
{
    cmd_incantation_t *current = TAILQ_FIRST(&s->_head_incantation);

    while (current) {
        if (current->organizer == c)
            return current;
        if (player_is_participant(current, c))
            return current;
        current = TAILQ_NEXT(current, entries);
    }
    return NULL;
}

bool player_still_on_pos(cmd_incantation_t *current)
{
    client_socket_t *cli;

    for (int i = 0; current->number_of_participants - 1; i++) {
        if (!current->participants[i])
            return false;
        cli = current->participants[i];
        if (cli->player->_pos._x != current->tile_vector._x ||
        cli->player->_pos._y != current->tile_vector._y)
            return false;
    }
    return true;
}

void free_incantation(server_t *server, cmd_incantation_t *current)
{
    TAILQ_REMOVE(&server->_head_incantation, current, entries);
    free(current->participants);
    free(current);
}

bool check_post_incantation(server_t *server, client_socket_t *client)
{
    cmd_incantation_t *current = find_correct_incantation(server, client);
    incantation_t incantation = incantations[client->player->_level - 1];
    tiles_t *tile = server->grid->_tiles[current->tile_vector._y]
    [current->tile_vector._x];

    if (!player_still_on_pos(current)) {
        printf("not all players are on the same tile\n");
        return false;
    }
    for (int i = 0; i < 7; i++) {
        if (tile->_items[i] < incantation._objects_required[i]) {
            printf("not enough items\n");
            return false;
        }
        tile->_items[i] -= incantation._objects_required[i];
    }
    return true;
}
