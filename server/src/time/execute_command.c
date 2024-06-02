/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** execute_command.c
*/

#include "../../include/commands.h"

void execute_command(server_t *server)
{
    delayed_command_t *delayed_command;

    TAILQ_FOREACH(delayed_command, &server->_head_delayed_commands, entries) {
        if (delayed_command->_delay <= 0) {
            delayed_command->_func(server, delayed_command->_args,
            delayed_command->_client);
            TAILQ_REMOVE(&server->_head_delayed_commands, delayed_command,
            entries);
            free(delayed_command);
        } else {
            delayed_command->_delay--;
        }
    }
    return;
}

void actl(server_t *server, client_socket_t *c, command_t *cmd, char *args)
{
    delayed_command_t *delayed_command = (delayed_command_t *)
    malloc(sizeof(delayed_command_t));

    delayed_command->_func = cmd->ptr;
    delayed_command->_args = args;
    delayed_command->_client = c;
    delayed_command->_delay = cmd->time;
    TAILQ_INSERT_TAIL(&server->_head_delayed_commands, delayed_command,
    entries);
    free(cmd);
}
