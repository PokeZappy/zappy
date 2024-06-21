/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_gui5.c
*/

#include "../../../include/commands.h"

void cmd_sst(server_t *server, char *args, client_socket_t *client)
{
    int new_f = atoi(args + 4);

    server->arguments->_f = new_f;
    dprintf(get_gui(server)->socket, "sst %d\n", new_f);
}
