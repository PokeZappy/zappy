/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue.c
*/

#include "../../include/commands.h"

void execute_command(server_t *server)
{
    delayed_command_t *delayed_command;
    delayed_command_t *tmp;

    delayed_command = TAILQ_FIRST(&server->_head_delayed_commands);
    while (delayed_command != NULL) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (delayed_command->_delay <= 0) {
            delayed_command->_func(server, delayed_command->_args,
                delayed_command->_client);
            TAILQ_REMOVE(&server->_head_delayed_commands,
                delayed_command, entries);
            free(delayed_command->_args);
            free(delayed_command);
        } else {
            delayed_command->_delay--;
        }
        delayed_command = tmp;
    }
    return;
}

void actl(server_t *server, client_socket_t *c, command_t *cmd, char *args)
{
    delayed_command_t *delayed_command = (delayed_command_t *)
    malloc(sizeof(delayed_command_t));
    int how_many = how_many_in_queue(server, c);

    delayed_command->_func = cmd->ptr;
    delayed_command->_args = strdup(args);
    delayed_command->_client = c;
    if (how_many < 10) {
        if (how_many == 0)
            delayed_command->_delay = cmd->time;
        else
            delayed_command->_delay = calc_delay(server, c, cmd->time);
    } else {
        delete_last_cmd(server, c);
        delayed_command->_delay = calc_delay(server, c, cmd->time);
    }
    TAILQ_INSERT_TAIL(&server->_head_delayed_commands, delayed_command,
    entries);
    free(cmd);
}
