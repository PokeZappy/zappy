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
    delayed_command = TAILQ_FIRST(&server->_head_delayed_commands);
    while (delayed_command != NULL) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (is_time_g_or_e(&current_time, &delayed_command->_delay)) {
        delayed_command->_func(server, delayed_command->_args,
        delayed_command->_client);
            TAILQ_REMOVE(&server->_head_delayed_commands,
            delayed_command, entries);
            free(delayed_command->_args);
            free(delayed_command);
        }
        delayed_command = tmp;
    }
}

void print_queue(server_t *server)
{
    delayed_command_t *delayed_command;

    TAILQ_FOREACH(delayed_command, &server->_head_delayed_commands, entries) {
        printf("Command: %s\n", delayed_command->_args);
        printf("Delay: %ld : %ld\n", delayed_command->_delay.tv_sec,
        delayed_command->_delay.tv_usec);
    }
}

void icii_actl(server_t *server, client_socket_t *c, command_t *cmd, char *a)
{
    cmd_incantation_t *cmd_incantation;

    if (icii(server, c))
        return;
    actl(server, c, cmd, a);
}

void actl(server_t *server, client_socket_t *c, command_t *cmd, char *args)
{
    delayed_command_t *delayed_command = (delayed_command_t *)
    malloc(sizeof(delayed_command_t));
    int how_many = how_many_in_queue(server, c);

    delayed_command->_func = cmd->ptr;
    delayed_command->_args = strdup(args);
    delayed_command->_client = c;
    delayed_command->_delay = cmd->delay;
    if (how_many < 10) {
        if (how_many != 0)
            calc_delay(server, c, cmd->delay);
    } else {
        delete_last_cmd(server, c);
        calc_delay(server, c, cmd->delay);
    }
    TAILQ_INSERT_TAIL(&server->_head_delayed_commands, delayed_command,
    entries);
    print_queue(server);
    free(cmd);
}

void break_player_queue(server_t *server, client_socket_t *c)
{
    delayed_command_t *delayed_command;
    delayed_command_t *tmp;

    delayed_command = TAILQ_FIRST(&server->_head_delayed_commands);
    while (delayed_command != NULL) {
        tmp = TAILQ_NEXT(delayed_command, entries);
        if (delayed_command->_client == c) {
            TAILQ_REMOVE(&server->_head_delayed_commands, delayed_command,
            entries);
            free(delayed_command->_args);
            free(delayed_command);
        }
        delayed_command = tmp;
    }
}