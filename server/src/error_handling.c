/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** error_handling.c
*/

#include "../include/error_handling.h"

static void print_help(void)
{
    printf("USAGE: help message shaisssss !\n");
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
    if (ac != 8) {
        print_error();
        return 84;
    }
    return 0;
}
