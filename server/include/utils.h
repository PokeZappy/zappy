/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** utils.h
*/

#pragma once

#include "server.h"

client_socket_t *find_client_by_socket(server_t *server, int socket);
player_t *find_player_by_socket(server_t *server, int socket);
client_socket_t *find_gui(server_t *server, int socket);
client_socket_t *find_client_by_playerid(server_t *server, int id);
bool is_client_gui(client_socket_t *client);

char **decompose_output(char *output);
void free_str_array(char **array);
