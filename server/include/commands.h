/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** commands.h
*/

#pragma once

#include "server.h"

typedef struct command_s {
    char *name;
    void (*ptr)(server_t *server, char *args, int client_nbr);
} command_t;

// -- PLAYER -- //
void cmd_forward(server_t *server, char *args, int client_nbr);
void cmd_right(server_t *server, char *args, int client_nbr);
void cmd_left(server_t *server, char *args, int client_nbr);
void cmd_look(server_t *server, char *args, int client_nbr);
void cmd_inventory(server_t *server, char *args, int client_nbr);
void cmd_broadcast(server_t *server, char *args, int client_nbr);
void cmd_slot(server_t *server, char *args, int client_nbr);
void cmd_fork(server_t *server, char *args, int client_nbr);
void cmd_eject(server_t *server, char *args, int client_nbr);
void cmd_dead(server_t *server, char *args, int client_nbr);
void cmd_connect_nbr(server_t *server, char *args, int client_nbr);
void cmd_take_object(server_t *server, char *args, int client_nbr);
void cmd_set_object(server_t *server, char *args, int client_nbr);
void cmd_incantation(server_t *server, char *args, int client_nbr);

// -- GUI -- //
void cmd_msz(server_t *server, char *args, int client_nbr);
void cmd_bct(server_t *server, char *args, int client_nbr);
void cmd_mct(server_t *server, char *args, int client_nbr);
void cmd_tna(server_t *server, char *args, int client_nbr);
void cmd_pnw(server_t *server, char *args, int client_nbr);
void cmd_ppo(server_t *server, char *args, int client_nbr);
void cmd_plv(server_t *server, char *args, int client_nbr);
void cmd_pin(server_t *server, char *args, int client_nbr);
void cmd_pex(server_t *server, char *args, int client_nbr);
void cmd_pbc(server_t *server, char *args, int client_nbr);
void cmd_pic(server_t *server, char *args, int client_nbr);
void cmd_pie(server_t *server, char *args, int client_nbr);
void cmd_pfk(server_t *server, char *args, int client_nbr);
void cmd_pdr(server_t *server, char *args, int client_nbr);
void cmd_pgt(server_t *server, char *args, int client_nbr);
void cmd_pdi(server_t *server, char *args, int client_nbr);
void cmd_enw(server_t *server, char *args, int client_nbr);
void cmd_ebo(server_t *server, char *args, int client_nbr);
void cmd_edi(server_t *server, char *args, int client_nbr);
void cmd_sgt(server_t *server, char *args, int client_nbr);
void cmd_sst(server_t *server, char *args, int client_nbr);
void cmd_seg(server_t *server, char *args, int client_nbr);
void cmd_smg(server_t *server, char *args, int client_nbr);
void cmd_suc(server_t *server, char *args, int client_nbr);
void cmd_sbp(server_t *server, char *args, int client_nbr);

// -- SERVER -- //
void cmd_unknown(server_t *server, char *args, int client_nbr);
