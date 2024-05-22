/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** server.h
*/

#pragma once

#include "parsing.h"
#include "team.h"
#include "grid.h"
#include <sys/queue.h>
#include <netinet/in.h>

typedef struct server_s {
    server_arg_t *arguments; // arguments of the server
    int socket; // socket of the server
    struct sockaddr_in sock_in; // address of the server
    fd_set read_fds; // read file descriptor
    fd_set write_fds; // write file descriptor
    grid_t *grid; // grid of the server
    TAILQ_HEAD(, player_s) _head_player; // list of players
    TAILQ_HEAD(, team_s) _head_team; // list of teams
} server_t;

server_t *init_server(server_arg_t *arguments);
void free_server(server_t *server);
void add_player_to_server(server_t *server, player_t *player);
void remove_player_from_server(server_t *server, player_t *player);
