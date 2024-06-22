/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** command_gui4.c
*/

#include "../../../include/commands.h"

void cmd_sgt(server_t *server, char *args, client_socket_t *client)
{
    dprintf(client->socket, "sgt %d\n", server->arguments->_f);
    // printf("sgt\n");
}
