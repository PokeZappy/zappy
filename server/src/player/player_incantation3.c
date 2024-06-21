/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/server.h"

bool is_participant(cmd_incantation_t *cu, client_socket_t *cl)
{
    for (int i = 0; cu->participants[i] != NULL; i++) {
        if (cu->participants[i] == cl)
            return true;
    }
    return false;
}

delayed_command_t *ficbcq(server_t *s, client_socket_t *c)
{
    delayed_command_t *command;
    cmd_incantation_t *incantation;

    TAILQ_FOREACH(command, &s->_head_delayed_commands, entries) {
        if (strncmp(command->_args, "Incantation", 11) == 0) {
            incantation = find_incantation(s, command->_client);
            if (is_participant(incantation, c))
                return command;
        }
    }
    return NULL;
}
