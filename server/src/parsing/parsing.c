/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** parsing.c
*/

#include "../../include/parsing.h"
#include "../../include/free.h"

static int is_number(char *str)
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
        while (av[i] && av[i][0] != '-') {
            names++;
            i++;
        }
        return names;
    }
    return 84;
}

static int create_tab(int ac, char **av, server_arg_t *args, int i)
{
    args->n = (char **)malloc(sizeof(char *) * (args->num_names + 1));
    args->n[args->num_names] = NULL;
    i--;
    for (int j = 0; j < args->num_names; j++) {
        i++;
        args->n[j] = strdup(av[i]);
    }
    return i;
}

static int is_an_arg(char *str)
{
    if (strcmp(str, "-p") != 0 && strcmp(str, "-c") != 0 &&
        strcmp(str, "-x") != 0 && strcmp(str, "-f") != 0 &&
        strcmp(str, "-y") != 0 && strcmp(str, "-n") != 0)
        return 0;
    return 1;
}

static int check_arg(int ac, char **av, server_arg_t *args, int i)
{
    if (strcmp(av[i - 1], "-p") == 0 && i < ac && is_number(av[i]))
        args->p = atoi(av[i]);
    if (strcmp(av[i - 1], "-x") == 0 && i < ac && is_number(av[i]))
        args->x = atoi(av[i]);
    if (strcmp(av[i - 1], "-y") == 0 && i < ac && is_number(av[i]))
        args->y = atoi(av[i]);
    if (strcmp(av[i - 1], "-c") == 0 && i < ac && is_number(av[i]))
        args->c = atoi(av[i]);
    if (strcmp(av[i - 1], "-f") == 0 && i < ac && is_number(av[i]))
        args->f = atoi(av[i]);
    if (strcmp(av[i - 1], "-n") == 0 && i < ac)
        return create_tab(ac, av, args, i);
    if (!is_an_arg(av[i - 1]) || (i + 1 > ac)) {
        fprintf(stderr, "parsing: Incorrect arguments {%s}.\n", av[i - 1]);
        return -84;
    }
    return i;
}

static int parsing_arg(int ac, char **av, server_arg_t *args)
{
    int temp = 0;

    for (int i = 1; i < ac; i++) {
        i++;
        temp = check_arg(ac, av, args, i);
        if (temp == -84) {
            free_server_arg(args);
            return 84;
        }
        i = temp;
    }
    if (args->x < 10 || args->x > 30 || args->y < 10 || args->y > 30) {
        free_server_arg(args);
        return 84;
    }
    return 0;
}

static server_arg_t *parsing_av(int ac, char **av, server_arg_t *arg)
{
    arg->p = -84;
    arg->x = -84;
    arg->y = -84;
    arg->c = -84;
    arg->f = -84;
    if (parsing_arg(ac, av, arg) == 84) {
        return NULL;
    }
    if (arg->p == -84 || arg->x == -84 || arg->y == -84 ||
        arg->c == -84 || arg->f == -84 || !arg->n) {
        return NULL;
    }
    return arg;
}

server_arg_t *parsing(int ac, char **av)
{
    int num_names = count_names(av);
    server_arg_t *args = (server_arg_t *)malloc(sizeof(server_arg_t));

    if (args == NULL) {
        fprintf(stderr, "parsing: Memory allocation failed\n");
        return NULL;
    }
    if (num_names == 84) {
        fprintf(stderr, "parsing: Incorrect arguments.\n");
        free_server_arg(args);
        return NULL;
    }
    args->num_names = num_names;
    return parsing_av(ac, av, args);
}
