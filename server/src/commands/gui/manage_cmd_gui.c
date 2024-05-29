/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_commands.c
*/

#include "../../../include/commands.h"

static void m_cmd_2(char *command, client_socket_t *client, server_t *server)
{
    return;
}

void manage_cmd_gui(char *command, client_socket_t *client, server_t *server)
{
    if (strcmp(command, "EXIT") == 0)
        return exit_command(client, server);
    if (strcmp(command, "CLIENT_LIST") == 0)
        return print_client_list(server);
    return m_cmd_2(command, client, server);
}
