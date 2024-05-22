/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** error_handling.c
*/

#include "../../include/error_handling.h"

static void print_help(void)
{
    printf("USAGE: ./zappy_server -p [port] -x [width] -y [height] ");
    printf("-n {name1} {name2} ... {namex} -c [clientsNb] -f [freq]\n");
    printf("\t-p port  \tport number\n");
    printf("\t-x width \twidth of the world\n");
    printf("\t-y height\theight of the world\n");
    printf("\t-n namex \tlist of names of the team\n");
    printf("\t-c clNb  \tnumber of authorized clients per team\n");
    printf("\t-f freq  \treciprocal of time unit for execution of actions\n");
}

static void print_error(void)
{
    fprintf(stderr, "error_handling: Not enough or too many arguments.\n");
}

int error_handling(int ac, char **av)
{
    if (av[1] && strcmp(av[1], "-help") == 0) {
        print_help();
        return 1;
    }
    if (ac < 13) {
        print_error();
        return 84;
    }
    return 0;
}
