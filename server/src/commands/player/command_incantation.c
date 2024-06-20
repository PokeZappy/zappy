/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_incantation.c
*/

#include "../../../include/commands.h"
#include "../../../include/incantation.h"
#include "../../../include/utils.h"

void cmd_pre_incant(server_t *server, char *args, client_socket_t *client)
{
    command_t *cmd = (command_t *)malloc(sizeof(command_t));
    player_t *player = client->player;
    timeval_t wait;

    cmd->name = "incantation";
    cmd->ptr = cmd_post_incant;
    cmd->time = 300;
    if (!check_incantation(server, player)) {
        dprintf(client->socket, "ko\n");
        return;
    }
    create_current_incantation(server, client->player);
    gettimeofday(&wait, NULL);
    add_seconds(&wait, cmd->time / (float)server->arguments->_f);
    cmd->delay = wait;
    dprintf(client->socket, "Elevation underway\n");
    actl(server, client, cmd, args);
    printf("pre incant\n");
}

void cmd_post_incant(server_t *server, char *args, client_socket_t *client)
{
    player_t *player = client->player;
    cmd_incantation_t *current = find_correct_incantation(server, client);

    if (!check_incantation(server, player)) {
        dprintf(client->socket, "ko\n");
        return (void)dprintf(get_gui(server)->socket, "pie %d %d ko\n",
        player->_pos._x, player->_pos._y);
    }
    dprintf(get_gui(server)->socket, "pie %d %d ok\n", player->_pos._x,
            player->_pos._y);
    for (int i = 0; i < current->number_of_participants; i++) {
        current->participants[i]->player->_level++;
        dprintf(current->participants[i]->socket, "Current level: %d\n",
            current->participants[i]->player->_level);
        dprintf(get_gui(server)->socket, "plv %d %d\n",
            current->participants[i]->player->_id,
            current->participants[i]->player->_level);
    }
    free_incantation(server, current);
}
