/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/server.h"

void send_gui_elevation(server_t *s, cmd_incantation_t *c, player_t *p)
{
    char buffer[4096];

    sprintf(buffer, "pic %d %d %d", p->pos.x,
    p->pos.y, p->level);
    for (int i = 0; i < c->number_of_participants; i++) {
        sprintf(buffer, "%s %d", buffer,
        c->participants[i]->id);
        dprintf(c->participants[i]->socket,
                "Elevation underway\n");
    }
    sprintf(buffer, "%s\n", buffer);
    dprintf(get_gui(s)->socket, "%s", buffer);
}

bool is_participant(cmd_incantation_t *cu, client_socket_t *cl)
{
    for (int i = 0; i < cu->number_of_participants; i++) {
        if (cu->participants[i] == cl)
            return true;
    }
    return false;
}

delayed_command_t *ficbcq(server_t *s, client_socket_t *c)
{
    delayed_command_t *command;
    cmd_incantation_t *incantation;

    TAILQ_FOREACH(command, &s->head_delayed_commands, entries) {
        if (strncmp(command->args, "Incantation", 11) == 0) {
            incantation = find_incantation(s, command->client);
            if (is_participant(incantation, c))
                return command;
        }
    }
    return NULL;
}
