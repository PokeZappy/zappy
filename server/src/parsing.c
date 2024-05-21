/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** parsing.c
*/

#include "../include/parsing.h"
#include "../include/free.h"

static int check_arg(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] > '9' || str[i] < '0')
            return 0;
    }
    return 1;
}

static int count_names(char **av)
{
    int i = 0;
    int names = 0;

    while (av[i]) {
        if (strcmp(av[i], "-n") != 0) {
            i++;
            continue;
        }
        i++;
        while (av[i][0] != '-') {
            names++;
            i++;
        }
        return names;
    }
    return 84;
}

server_arg_t *parsing(int ac, char **av)
{
    int num_names = count_names(av);
    int is_p = 0, is_x = 0, is_y = 0, is_c = 0, is_f = 0, is_n = 0;
    server_arg_t *args = (server_arg_t *)malloc(sizeof(server_arg_t));
    args->_n = NULL;

    if (args == NULL) {
        fprintf(stderr, "parsing: Memory allocation failed\n");
        return NULL;
    } if (num_names == 84) {
        fprintf(stderr, "parsing: Incorrect arguments.\n");
        free_server_arg(args);
        return NULL;
    }

    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0 && i + 1 < ac && check_arg(av[i + 1])) {
            is_p = 1;
            args->_p = atoi(av[++i]);
        } else if (strcmp(av[i], "-x") == 0 && i + 1 < ac && check_arg(av[i + 1])) {
            is_x = 1;
            args->_x = atoi(av[++i]);
        } else if (strcmp(av[i], "-y") == 0 && i + 1 < ac && check_arg(av[i + 1])) {
            is_y = 1;
            args->_y = atoi(av[++i]);
        } else if (strcmp(av[i], "-c") == 0 && i + 1 < ac && check_arg(av[i + 1])) {
            is_c = 1;
            args->_c = atoi(av[++i]);
        } else if (strcmp(av[i], "-f") == 0 && i + 1 < ac && check_arg(av[i + 1])) {
            is_f = 1;
            args->_f = atoi(av[++i]);
        } else if (strcmp(av[i], "-n") == 0 && i + 1 < ac) {
            is_n = 1;
            args->_n = (char **)malloc(sizeof(char *) * (num_names + 1));
            args->_n[num_names] = NULL;

            for (int j = 0; j < num_names; j++) {
                i++;
                args->_n[j] = strdup(av[i]);
            }

        } else {
            fprintf(stderr, "parsing: Incorrect arguments {%s}.\n", av[i]);
            free_server_arg(args);
            return NULL;
        }
    }

    if (!is_p || !is_x || !is_y || !is_c || !is_f || !is_n) {
        return NULL;
    }

    return args;
}
