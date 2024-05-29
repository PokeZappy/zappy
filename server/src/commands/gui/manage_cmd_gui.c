/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_commands.c
*/

#include "../../../include/commands.h"

static void m_cmd_2(char *command, client_socket_t *client, server_t *server)
{
    if (strncmp(command, "pin ", 4) == 0)
        return cmd_pin(server, command, client);
    if (strncmp(command, "sgt ", 4) == 0)
        return cmd_sgt(server, command, client);
    if (strncmp(command, "sst ", 4) == 0)
        return cmd_sst(server, command, client);
}

void manage_cmd_gui(char *command, client_socket_t *client, server_t *server)
{
    if (strcmp(command, "EXIT") == 0)
        return exit_command(client, server);
    if (strcmp(command, "CLIENT_LIST") == 0)
        return print_client_list(server);
    if (strncmp(command, "msz ", 4) == 0)
        return cmd_msz(server, command, client);
    if (strncmp(command, "bct ", 4) == 0)
        return cmd_bct(server, command, client);
    if (strncmp(command, "mct ", 4) == 0)
        return cmd_mct(server, command, client);
    if (strncmp(command, "tna ", 4) == 0)
        return cmd_tna(server, command, client);
    if (strncmp(command, "pnw ", 4) == 0)
        return cmd_pnw(server, command, client);
    if (strncmp(command, "ppo ", 4) == 0)
        return cmd_ppo(server, command, client);
    if (strncmp(command, "plv ", 4) == 0)
        return cmd_plv(server, command, client);
    return m_cmd_2(command, client, server);
}
