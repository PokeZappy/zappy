/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_incantation.c
*/

#include "../../../include/commands.h"
#include "../../../include/utils.h"

void cmd_pre_incant(server_t *server, char *args, client_socket_t *client)
{
    command_t *cmd = (command_t *)malloc(sizeof(command_t));
    player_t *player = client->player;

    printf("\n\nPRE Incantation\n\n");
    cmd->name = "Incantation";
    cmd->ptr = cmd_post_incant;
    cmd->time = 300;
    if (!check_incantation(server, player)) {
        dprintf(client->socket, "ko\n");
        return;
    }
    create_current_incantation(server, client->player);
    gettimeofday(&cmd->delay, NULL);
    add_seconds(&cmd->delay, cmd->time / (float)server->arguments->f);
    actl(server, client, cmd, args);
}

void is_win(server_t *server, client_socket_t *client, cmd_incantation_t *c)
{
    if (client->player->level == 8) {
        dprintf(client->socket, "win\n");
        dprintf(get_gui(server)->socket, "seg %s\n",
        client->player->team->name);
    }
    free_incantation(server, c);
}

void cmd_post_incant(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    cmd_incantation_t *current = find_incantation(server, client);

    printf("\n\nPOST Incantation\n\n");
    if (!check_post_incantation(server, client)) {
        printf("Incantation failed\n"),
        dprintf(client->socket, "ko\n");
        dprintf(get_gui(server)->socket, "pie %d %d ko\n",
        player->pos.x, player->pos.y);
        return;
    }
    printf("Incantation success\n");
    dprintf(get_gui(server)->socket, "pie %d %d ok\n", player->pos.x,
            player->pos.y);
    for (int i = 0; i < current->number_of_participants; i++) {
        current->participants[i]->player->level++;
        dprintf(current->participants[i]->socket, "Current level: %d\n",
            current->participants[i]->player->level);
        dprintf(get_gui(server)->socket, "plv %d %d\n",
            current->participants[i]->id,
            current->participants[i]->player->level);
    }
    is_win(server, client, current);
}
