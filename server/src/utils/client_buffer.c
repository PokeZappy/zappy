/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** incantation.c
*/

#include "../../include/server.h"

void print_buffer(int socket, char *buffer)
{
    size_t len = strlen(buffer);
    char *temp;
    size_t n;

    while (len > 0) {
        n = len < 4095 ? len : 4095;
        temp = strndup(buffer, n);
        dprintf(socket, "%s", temp);
        free(temp);
        buffer += n;
        len -= n;
    }
}
