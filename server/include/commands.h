/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** commands.h
*/

#pragma once

#include "server.h"

#include <math.h>

struct server_s;
typedef struct server_s server_t;

struct client_socket_s;
typedef struct client_socket_s client_socket_t;

typedef struct delayed_command_s {
    void *_func;
    char **_args;
    client_socket_t *_client;
    int _delay;
    TAILQ_ENTRY(delayed_command_s) entries;
} delayed_command_t;

typedef struct command_s {
    char *name;
    void (*ptr)(server_t *server, char *args, client_socket_t *client);
} command_t;

void manage_cmd_play(char *command, client_socket_t *client, server_t *server);
void manage_cmd_gui(char *command, client_socket_t *client, server_t *server);

// -- PLAYER -- //
void cmd_forward(server_t *server, client_socket_t *client);
void cmd_right(server_t *server, client_socket_t *client);
void cmd_left(server_t *server, client_socket_t *client);
void cmd_look(server_t *server, char *args, client_socket_t *client);
void cmd_inventory(server_t *server, client_socket_t *client);
void cmd_broadcast(server_t *server, char *args, client_socket_t *client);
void cmd_slot(server_t *server, char *args, client_socket_t *client);
void cmd_fork(server_t *server, char *args, client_socket_t *client);
void cmd_eject(server_t *server, char *args, client_socket_t *client);
void cmd_dead(server_t *server, char *args, client_socket_t *client);
void cmd_connect_nbr(server_t *server, client_socket_t *client);
void cmd_take(server_t *server, char *args, client_socket_t *client);
void cmd_set(server_t *server, char *args, client_socket_t *client);
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

// -- MY_CMD -- //
void print_client_list(client_socket_t *client, server_t *server);
void exit_command(client_socket_t *client, server_t *server);
void hack_player_pos(client_socket_t *client, server_t *server, char *args);
void hack_player_dir(client_socket_t *client, server_t *server, char *args);
