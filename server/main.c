/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** main.c
*/

#include "include/error_handling.h"
#include "include/parsing.h"
#include "include/free.h"
#include "include/zappy_server.h"

int main(int ac, char **av)
{
    server_arg_t *args;
    int error = error_handling(ac, av);

    if (error == 84)
        return 84;
    if (error == 1)
        return 0;
    args = parsing(ac, av);
    if (args == NULL) {
        free_server_arg(args);
        return 84;
    }
    zappy_server(args);
    free_server_arg(args);
    return 0;
}
