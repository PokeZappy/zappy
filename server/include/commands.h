/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** commands.h
*/

#pragma once

#include "server.h"

struct server_s;
typedef struct server_s server_t;

struct client_socket_s;
typedef struct client_socket_s client_socket_t;

typedef struct command_s {
    char *name;
    void (*ptr)(server_t *server, char *args, client_socket_t *client);
} command_t;

void manage_command(char *commands, client_socket_t *client, server_t *server);

// -- PLAYER -- //
void cmd_forward(server_t *server, char *args, client_socket_t *client);
void cmd_right(server_t *server, char *args, client_socket_t *client);
void cmd_left(server_t *server, char *args, client_socket_t *client);
void cmd_look(server_t *server, char *args, client_socket_t *client);
void cmd_inventory(server_t *server, char *args, client_socket_t *client);
void cmd_broadcast(server_t *server, char *args, client_socket_t *client);
void cmd_slot(server_t *server, char *args, client_socket_t *client);
void cmd_fork(server_t *server, char *args, client_socket_t *client);
void cmd_eject(server_t *server, char *args, client_socket_t *client);
void cmd_dead(server_t *server, char *args, client_socket_t *client);
void cmd_connect_nbr(server_t *server, char *args, client_socket_t *client);
void cmd_take_object(server_t *server, char *args, client_socket_t *client);
void cmd_set_object(server_t *server, char *args, client_socket_t *client);
void cmd_incantation(server_t *server, char *args, client_socket_t *client);

// -- GUI -- //
void cmd_msz(server_t *server, char *args, client_socket_t *client);
void cmd_bct(server_t *server, char *args, client_socket_t *client);
void cmd_mct(server_t *server, char *args, client_socket_t *client);
void cmd_tna(server_t *server, char *args, client_socket_t *client);
void cmd_pnw(server_t *server, char *args, client_socket_t *client);
void cmd_ppo(server_t *server, char *args, client_socket_t *client);
void cmd_plv(server_t *server, char *args, client_socket_t *client);
void cmd_pin(server_t *server, char *args, client_socket_t *client);
void cmd_sgt(server_t *server, char *args, client_socket_t *client);
void cmd_sst(server_t *server, char *args, client_socket_t *client);

// -- SERVER -- //
void cmd_unknown(server_t *server, char *args, client_socket_t *client);
