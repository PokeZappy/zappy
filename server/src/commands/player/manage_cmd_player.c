/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_command.c
*/

#include "../../../include/commands.h"

static void m_cmd_2(char *command, client_socket_t *client, server_t *server)
{
    if (strncmp(command, "take ", 5) == 0)
        return cmd_take(server, command, client);
    if (strncmp(command, "set ", 4) == 0)
        return cmd_set(server, command, client);
    if (strncmp(command, "incantation ", 12) == 0)
        return cmd_incantation(server, command, client);
    if (strncmp(command, "slot ", 5) == 0)
        return cmd_slot(server, command, client);
    if (strncmp(command, "fork ", 5) == 0)
        return cmd_fork(server, command, client);
    if (strncmp(command, "dead ", 5) == 0)
        return cmd_dead(server, command, client);
    if (strncmp(command, "connect_nbr", 11) == 0)
        return cmd_connect_nbr(server, client);
    if (strncmp(command, "HACK_DIR ", 9) == 0)
        return hack_player_dir(client, server, command + 9);
    if (strncmp(command, "HACK_POS ", 9) == 0)
        return hack_player_pos(client, server, command + 9);
}

void manage_cmd_play(char *command, client_socket_t *client, server_t *server)
{
    if (strcmp(command, "EXIT") == 0)
        return exit_command(client, server);
    if (strcmp(command, "CLIENT_LIST") == 0)
        return print_client_list(server);
    if (strncmp(command, "forward", 7) == 0)
        return cmd_forward(server, client);
    if (strncmp(command, "right", 5) == 0)
        return cmd_right(server, client);
    if (strncmp(command, "left", 4) == 0)
        return cmd_left(server, client);
    if (strncmp(command, "look ", 5) == 0)
        return cmd_look(server, command, client);
    if (strncmp(command, "inventory", 9) == 0)
        return cmd_inventory(server, client);
    if (strncmp(command, "broadcast", 9) == 0)
        return cmd_broadcast(server, command, client);
    if (strncmp(command, "eject ", 6) == 0)
        return cmd_eject(server, command, client);
    return m_cmd_2(command, client, server);
}
