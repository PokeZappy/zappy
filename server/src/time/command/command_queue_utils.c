/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue_utils.c
*/

#include "../../../include/commands.h"

timeval_t longest_delay_for_client(server_t *server, client_socket_t *client)
{
    timeval_t longest_delay = {0, 0};
    delayed_command_t *delayed_command = NULL;
    delayed_command_t *tmp = NULL;

    for (delayed_command = TAILQ_FIRST(&server->head_delayed_commands);
    delayed_command != NULL;
    delayed_command = tmp) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (delayed_command->client == client
        && compare_timeval(&delayed_command->delay, &longest_delay)) {
            longest_delay = delayed_command->delay;
        }
    }
    return longest_delay;
}

delayed_command_t *last_client_command(server_t *server, client_socket_t *c)
{
    timeval_t longest_delay = {0, 0};
    delayed_command_t *delayed_command = NULL;
    delayed_command_t *tmp = NULL;
    delayed_command_t *last_command = NULL;

    for (delayed_command = TAILQ_FIRST(&server->head_delayed_commands);
    delayed_command != NULL;
    delayed_command = tmp) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (delayed_command->client == c
        && compare_timeval(&delayed_command->delay, &longest_delay)) {
            longest_delay = delayed_command->delay;
            last_command = delayed_command;
        }
    }
    return last_command;
}

void calc_delay(server_t *server, client_socket_t *client, timeval_t delay)
{
    timeval_t last_delay = longest_delay_for_client(server, client);

    delay.tv_sec += last_delay.tv_sec;
    delay.tv_usec += last_delay.tv_usec;
    if (delay.tv_usec >= 1000000) {
        delay.tv_sec += last_delay.tv_usec / 1000000;
        delay.tv_usec %= 1000000;
    }
}

int how_many_in_queue(server_t *server, client_socket_t *client)
{
    int count = 0;
    delayed_command_t *delayed_command;

    TAILQ_FOREACH(delayed_command, &server->head_delayed_commands, entries)
        if (delayed_command->client == client)
            count++;
    return count;
}

void delete_last_cmd(server_t *server, client_socket_t *client)
{
    delayed_command_t *last_command = last_client_command(server, client);

    if (last_command != NULL) {
        TAILQ_REMOVE(&server->head_delayed_commands, last_command, entries);
        free(last_command->args);
        free(last_command);
    }
}
