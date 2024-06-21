/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** my_commands.c
*/

#include "../../include/commands.h"
#include "../../include/utils.h"

void exit_command(server_t *server, char *args, client_socket_t *client)
{
    printf("Client requested exit {%d}\n", client->_id);
    close(client->socket);
    TAILQ_REMOVE(&server->_head_client_sockets, client, entries);
    free_client(client);
}
