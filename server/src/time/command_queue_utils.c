/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue_utils.c
*/

#include "../../include/commands.h"


delayed_command_t *last_client_command(server_t *server, client_socket_t *c)
{
    delayed_command_t *delayed_command;
    delayed_command_t *last_command = NULL;

    TAILQ_FOREACH(delayed_command, &server->_head_delayed_commands, entries)
    if (delayed_command->_client == c)
        last_command = delayed_command;
    return last_command;
}

int calc_delay(server_t *server, client_socket_t *client, int delay)
{
    int delay_time = delay + last_client_command(server, client)->_delay;

    return delay_time;
}

int how_many_in_queue(server_t *server, client_socket_t *client)
{
    int count = 0;
    delayed_command_t *delayed_command;

    TAILQ_FOREACH(delayed_command, &server->_head_delayed_commands, entries)
    if (delayed_command->_client == client)
        count++;
    return count;
}

void delete_last_cmd(server_t *server, client_socket_t *client)
{
    delayed_command_t *last_command = last_client_command(server, client);

    if (last_command != NULL) {
        TAILQ_REMOVE(&server->_head_delayed_commands, last_command, entries);
        free(last_command->_args);
        free(last_command);
    }
}
