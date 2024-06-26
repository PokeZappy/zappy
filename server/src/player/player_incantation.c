/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/incantation.h"
#include "../../include/server.h"
#include "../../include/utils.h"

int player_samepos_and_level(server_t *server, player_t *player)
{
    client_socket_t *current;
    int number = 0;

    TAILQ_FOREACH(current, &server->head_client_sockets, entries) {
        if (!current->player)
            continue;
        if (current->player->pos.x == player->pos.x &&
            current->player->pos.y == player->pos.y &&
            current->player->level == player->level)
            number++;
    }
    return number;
}

bool check_incantation(server_t *server, player_t *player)
{
    incantation_t incantation = incantations[player->level - 1];
    int players = 0;
    tiles_t *tile = server->grid->tiles[player->pos.y][player->pos.x];

    for (int i = 0; i < 7; i++) {
        if (tile->items[i] < incantation.objects_required[i])
            return false;
    }
    players = player_samepos_and_level(server, player);
    if (players < incantation.players_required)
        return false;
    return true;
}

void add_delay_participants(server_t *server, client_socket_t *client)
{
    delayed_command_t *command = TAILQ_FIRST(&server->head_delayed_commands);

    while (command) {
        if (command->client == client)
            add_seconds(&command->delay, 300 / server->arguments->f);
        command = TAILQ_NEXT(command, entries);
    }
}

client_socket_t **rip(server_t *server, player_t *player)
{
    int players_count = player_samepos_and_level(server, player);
    client_socket_t **participants = (client_socket_t **)
    malloc(sizeof(player_t *) * (players_count + 1));
    client_socket_t *current;
    int i = 0;

    for (current = TAILQ_FIRST(&server->head_client_sockets);
    current; current = TAILQ_NEXT(current, entries)) {
        if (!current->player)
            continue;
        if (current->player->pos.x == player->pos.x &&
            current->player->pos.y == player->pos.y &&
            current->player->level == player->level) {
            participants[i] = find_client_by_player(server, current->player);
            add_delay_participants(server, participants[i]);
            i++;
        }
    }
    participants[players_count] = NULL;
    return participants;
}

static void print_incantation(cmd_incantation_t *incant)
{
    printf("Incantation: %d\n", incant->level);
    printf("Organizer: %d\n", incant->organizer->socket);
    printf("Participants: ");
    for (int i = 0; incant->participants[i]; i++)
        printf("\t%d : %d %d", incant->participants[i]->socket, incant->participants[i]->player->pos.x, incant->participants[i]->player->pos.y);
    printf("\n");
}

void create_current_incantation(server_t *server, player_t *player)
{
    cmd_incantation_t *cmd_incantation = (cmd_incantation_t *)
    malloc(sizeof(cmd_incantation_t));
    vector_t pos = {player->pos.y, player->pos.x};

    cmd_incantation->organizer = find_client_by_player(server, player);
    cmd_incantation->level = player->level;
    cmd_incantation->tile_vector = pos;
    cmd_incantation->participants = rip(server, player);
    cmd_incantation->number_of_participants =
    player_samepos_and_level(server, player);
    send_gui_elevation(server, cmd_incantation, player);
    print_incantation(cmd_incantation);
    TAILQ_INSERT_TAIL(&server->head_incantation, cmd_incantation, entries);
}
