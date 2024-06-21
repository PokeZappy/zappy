/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_command.c
*/

#include "../../../include/commands.h"

static const command_t commands[] = {
    {"Forward", cmd_forward, 7},
    {"Right", cmd_right, 7},
    {"Left", cmd_left, 7},
    {"Look", cmd_look, 7},
    {"Inventory", cmd_inventory, 1},
    {"Broadcast", cmd_broadcast, 7},
    {"Fork", cmd_fork, 42},
    {"Eject", cmd_eject, 7},
    {"dead", cmd_dead, 0},
    {"Connect_nbr", cmd_connect_nbr, 0},
    {"Take", cmd_take, 7},
    {"Set", cmd_set, 7},
    {"Incantation", cmd_pre_incant, 0},
    {"EXIT", exit_command, 0},
    {"test", cmd_forward, 300},
    {NULL, NULL, 0}
};

void manage_cmd_play(char *command, client_socket_t *client, server_t *server)
{
    command_t *cmd = (command_t *)malloc(sizeof(command_t));
    timeval_t wait;

    for (int i = 0; commands[i].name != NULL; i++) {
        if (strncmp(command, commands[i].name,
        strlen(commands[i].name)) == 0) {
            gettimeofday(&wait, NULL);
            add_seconds(&wait, commands[i].time
            / (float)server->arguments->_f);
            cmd->ptr = commands[i].ptr;
            cmd->time = commands[i].time;
            cmd->delay = wait;
            break;
        }
        if (commands[i + 1].name == NULL) {
            free(cmd);
            return;
        }
    }
    actl(server, client, cmd, command);
}
