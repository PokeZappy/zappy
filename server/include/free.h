/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** parsing.h
*/

#pragma once

#include "parsing.h"
#include "server.h"

struct server_s;
typedef struct server_s server_t;

void free_server_arg(server_arg_t *arguments);
void free_server(server_t *server);
void free_client(struct client_socket_s *client);
