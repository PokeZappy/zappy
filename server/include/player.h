/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** objects.h
*/

#pragma once

#include <stdbool.h>
#include "client.h"
#include "direction.h"
#include "vector.h"
#include "constant.h"
#include "team.h"
#include "server.h"
#include "grid.h"

struct server_s;
typedef struct server_s server_t;

struct team_s;
typedef struct team_s team_t;

struct cmd_incantation_s;
typedef struct cmd_incantation_s cmd_incantation_t;

struct client_socket_s;
typedef struct client_socket_s client_socket_t;

struct delayed_command_s;
typedef struct delayed_command_s delayed_command_t;

typedef struct player_s {
    int id; // id of the player
    vector_t pos; // position of the player
    direction_t direction; // looking direction of the player
    int level; // level of the player
    int inventory[ITEM_PER_TILE]; // list items on the tile
    int health; // health of the player
    struct team_s *team; // team of the player
    TAILQ_ENTRY(player_s) entries; // list of players
} player_t;

// -- PLAYER RELATED -- //
player_t *init_player(struct team_s *team, server_t *server);
void free_player(player_t *player);
void player_move(player_t *player, int map_width, int map_height);
void player_orientation(player_t *player, bool right);
char *print_player_inventory(player_t *player);
char *get_player_inventory(player_t *player);
bool player_eject(server_t *server, player_t *player);

// -- SERVER RELATED -- //
player_t *add_player_to_team(char *team_name, server_t *server);
char *player_look(server_t *server, player_t *player);
int nb_player_on_tile(server_t *server, vector_t tile_pos);
bool check_incantation(server_t *server, player_t *player);
bool check_post_incantation(server_t *server, client_socket_t *client);
void create_current_incantation(server_t *server, player_t *player);
bool is_participant(cmd_incantation_t *cu, client_socket_t *cl);
void free_incantation(server_t *server, cmd_incantation_t *current);
void check_death(server_t *server);
cmd_incantation_t *find_incantation(server_t *s, client_socket_t *c);
delayed_command_t *ficbcq(server_t *s, client_socket_t *c);
void send_gui_elevation(server_t *s, cmd_incantation_t *c, player_t *p);
client_socket_t *find_client_by_player(server_t *server, player_t *player);

// -- GRID RELATED -- //
int player_take_item(player_t *player, tiles_t *tile, char *item);
int player_drop_item(player_t *player, tiles_t *tile, char *item);
