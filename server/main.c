/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** main.c
*/

#include "include/error_handling.h"
#include "include/parsing.h"
#include "include/free.h"
#include "include/server.h"

/*int main(int ac, char **av)
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
    return 0;
}*/


int main()
{
    team_t *team = init_team("team1", 4);
    player_t *player = init_player(team);
    add_item_to_player(player, 0, 1);
    add_item_to_player(player, 1, 1);
    add_item_to_player(player, 4, 1);
    grid_t *grid = init_grid(10, 10);
    print_player_inventory(player);
    free(grid);
    free_player(player);
    free_team(team);
}
