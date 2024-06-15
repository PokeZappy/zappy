/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../../include/server.h"
/*
void time_manager(server_t *server)
{
    struct timeval tv;
    long long current_time;

    gettimeofday(&tv, NULL);
    current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (current_time - server->_time_manager->_last_time >= 1000) {
        server->_time_manager->_last_time = current_time;
        server->_time_manager->_elapsed_time++;
        if (server->_time_manager->_elapsed_time % 126 == 0)
            generate_resource(server->grid);
        if (server->_time_manager->_elapsed_time % 42 == 0)
            generate_eggs(server);
        if (server->_time_manager->_elapsed_time % 100 == 0)
            check_eggs(server);
        if (server->_time_manager->_elapsed_time % 100 == 0)
            check_players(server);
    }
}*/
