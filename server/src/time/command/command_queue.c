/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_queue.c
*/

#include "../../../include/commands.h"

void execute_command(server_t *server)
{
    timeval_t current_time;
    delayed_command_t *delayed_command;
    delayed_command_t *tmp;

    gettimeofday(&current_time, NULL);
    delayed_command = TAILQ_FIRST(&server->head_delayed_commands);
    while (delayed_command != NULL) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (is_time_g_or_e(&current_time, &delayed_command->delay)) {
        delayed_command->func(server, delayed_command->args,
        delayed_command->client);
            TAILQ_REMOVE(&server->head_delayed_commands,
            delayed_command, entries);
            free(delayed_command->args);
            free(delayed_command);
        }
        delayed_command = tmp;
    }
}

void print_queue(server_t *server)
{
    delayed_command_t *delayed_command;

    TAILQ_FOREACH(delayed_command, &server->head_delayed_commands, entries) {
        printf("Command: %s\n", delayed_command->args);
        printf("Delay: %ld : %ld\n", delayed_command->delay.tv_sec,
        delayed_command->delay.tv_usec);
    }
}

void actl(server_t *server, client_socket_t *c, command_t *cmd, char *args)
{
    delayed_command_t *delayed_command = (delayed_command_t *)
    malloc(sizeof(delayed_command_t));

    delayed_command->func = cmd->ptr;
    delayed_command->args = strdup(args);
    delayed_command->client = c;
    delayed_command->delay = cmd->delay;
    add_delay(server, c, delayed_command);
    TAILQ_INSERT_TAIL(&server->head_delayed_commands, delayed_command,
    entries);
    free(cmd);
}
