/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** client.h
*/

#pragma once

#include "constant.h"
#include "server.h"
#include "free.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/queue.h>

typedef struct client_socket_s {
    int socket;
    TAILQ_ENTRY(client_socket_s) entries;
} client_socket_t;
