/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../../include/server.h"

void launch_timed_function(server_t *server, int time_unit)
{
    execute_command(server);
    if (time_unit % 20 == 0) {
        generate_resource(server->grid);
        cmd_mct(server, NULL, get_gui(server));
    }
}

void time_manager(server_t *server)
{
    struct timeval tv;
    long long current_time;
    static long long static_time = 0;
    static int time_unit = 0;

    gettimeofday(&tv, NULL);
    current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (static_time == 0)
        static_time = current_time;
    if (current_time - static_time >= 1000 / (float)server->arguments->_f) {
        static_time = current_time;
        time_unit++;
        check_death(server);
        check_eggs(server);
    }
    launch_timed_function(server, time_unit);
}
