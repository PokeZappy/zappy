/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** server.h
*/

#pragma once

#include "parsing.h"
#include "team.h"
#include "player.h"
#include "grid.h"
#include "client.h"
#include "free.h"

#include <sys/queue.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct server_s {
    server_arg_t *arguments; // arguments of the server
    int socket; // socket of the server
    struct sockaddr_in sock_in; // address of the server
    fd_set read_fds; // read file descriptor
    fd_set write_fds; // write file descriptor
    grid_t *grid; // grid of the server
    TAILQ_HEAD(, team_s) _head_team; // list of teams
    TAILQ_HEAD(client_list, client_socket_s) _head_client_sockets; // players
    TAILQ_HEAD(, delayed_command_s) _head_delayed_commands; // list of commands
} server_t;

int zappy_server(server_arg_t *arguments);
