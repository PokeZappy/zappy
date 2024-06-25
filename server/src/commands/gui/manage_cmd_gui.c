/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** manage_commands.c
*/

#include "../../../include/commands.h"

static const command_t commands_gui[] = {
    {"msz", cmd_msz, 0},
    {"bct", cmd_bct, 0},
    {"mct", cmd_mct, 0},
    {"tna", cmd_tna, 0},
    {"ppo", cmd_ppo, 0},
    {"plv", cmd_plv, 0},
    {"pin", cmd_pin, 0},
    {"sgt", cmd_sgt, 0},
    {"sst", cmd_sst, 0},
    {"EXIT", exit_command, 0},
    {"HACK_DIR", hack_player_dir, 0},
    {"HACK_POS", hack_player_pos, 0},
    {"CLIENT_LIST", print_client_list, 0},
    {"EGG_LIST", print_egg_list, 0},
    {"HACK_GIVE", hack_player_give, 0},
    {"HACK_HEALTH", hack_player_health, 0},
    {"KILL", kill_player, 0},
    {NULL, NULL, 0}
};

client_socket_t *get_gui(server_t *server)
{
    client_socket_t *current = TAILQ_FIRST(&server->head_client_sockets);

    while (current) {
        if (current->is_gui == 1)
            return current;
        current = TAILQ_NEXT(current, entries);
    }
    return NULL;
}

void manage_cmd_gui(char *command, client_socket_t *client, server_t *server)
{
    for (int i = 0; commands_gui[i].name != NULL; i++) {
        if (strncmp(command, commands_gui[i].name,
                    strlen(commands_gui[i].name)) == 0) {
            return commands_gui[i].ptr(server, command, client);
        }
        if (commands_gui[i + 1].name == NULL) {
            dprintf(client->socket, "suc\n");
            return;
        }
    }
}
