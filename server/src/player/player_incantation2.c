/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/incantation.h"
#include "../../include/server.h"

cmd_incantation_t *find_incantation(server_t *s, client_socket_t *c)
{
    cmd_incantation_t *current = TAILQ_FIRST(&s->head_incantation);

    while (current) {
        if (current->organizer == c)
            return current;
        if (is_participant(current, c))
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

static void print_post_incantation(cmd_incantation_t *incant)
{
    printf("Incantation: %d\n", incant->level);
    printf("Organizer: %d\n", incant->organizer->id);
    printf("Position: %d %d\n", incant->tile_vector.x, incant->tile_vector.y);
    printf("Participants: \n");
    for (int i = 0; incant->participants[i]; i++)
        printf("  %d : %d %d\n", incant->participants[i]->id, incant->participants[i]->player->pos.x, incant->participants[i]->player->pos.y);
    printf("\n");
}

bool check_post_incantation(server_t *server, client_socket_t *client)
{
    cmd_incantation_t *current = find_incantation(server, client);
    incantation_t incantation = incantations[client->player->level - 1];
    tiles_t *tile = server->grid->tiles[current->tile_vector.y]
    [current->tile_vector.x];

    print_post_incantation(current);
    if (!player_still_onpos(current)) {
        free_incantation(server, current);
        return false;
    }
    for (int i = 0; i < 7; i++) {
        if (tile->items[i] < incantation.objects_required[i]) {
            free_incantation(server, current);
            return false;
        }
        tile->items[i] -= incantation.objects_required[i];
    }
    return true;
}
