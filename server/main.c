/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** main.c
*/

#include <time.h>
#include "include/error_handling.h"
#include "include/parsing.h"
#include "include/free.h"
#include "include/server.h"

int main(int ac, char **av)
{
    server_arg_t *args;
    int error = error_handling(ac, av);

    srand(time(NULL));
    if (error == 84)
        return 84;
    if (error == 1)
        return 0;
    args = parsing(ac, av);
    if (args == NULL) {
        printf("Error while parsing arguments\n");
        free_server_arg(args);
        return 84;
    }
    zappy_server(args);
    return 0;
}
