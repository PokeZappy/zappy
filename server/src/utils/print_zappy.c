/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-tom.blancheton
** File description:
** zappy_server.c
*/

#include "../../include/server.h"

void static print_title_1(void)
{
    printf("          _____                    _____                    ____");
    printf("_                    _____                _____          \n");
    printf("         /\\    \\                  /\\    \\                  /");
    printf("\\    \\                  /\\    \\              |\\    \\      ");
    printf("   \n");
    printf("        /::\\    \\                /::\\    \\                /:");
    printf(":\\    \\                /::\\    \\             |:");
    printf("\\____\\        \n");
    printf("        \\:::\\    \\              /::::\\    \\              /:");
    printf(":::\\    \\              /::::\\    \\            |::|   |      ");
    printf("  \n");
    printf("         \\:::\\    \\            /::::::\\    \\            /::");
    printf("::::\\    \\            /::::::\\    \\           |::|   |      ");
    printf("  \n");
    printf("          \\:::\\    \\          /:::/\\:::\\    \\          /::");
    printf(":/\\:::\\    \\          /:::/\\:::\\    \\          |::|   |   ");
    printf("     \n");
    printf("           \\:::\\    \\        /:::/__\\:::\\    \\        /:::");
    printf("/__\\:::\\    \\        /:::/__\\:::\\    \\         |::|   |   ");
    printf("     \n");
}

static void print_title_2(void)
{
    printf("            \\:::\\    \\      /::::\\   \\:::\\    \\      /:::");
    printf(":\\   \\:::\\    \\      /::::\\   \\:::\\    \\        |::|   |");
    printf("        \n");
    printf("             \\:::\\    \\    /::::::\\   \\:::\\    \\    /::::");
    printf("::\\   \\:::\\    \\    /::::::\\   \\:::\\    \\       |::|___|");
    printf("______  \n");
    printf("              \\:::\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/");
    printf("\\:::\\   \\:::\\____\\  /:::/\\:::\\   \\:::\\____\\      /::::");
    printf("::::\\    \\ \n");
    printf("_______________\\:::\\____\\/:::/  \\:::\\   \\:::\\____\\/:::/ ");
    printf(" \\:::\\   \\:::|    |/:::/  \\:::\\   \\:::|    |    /:::::::::");
    printf(":\\____\\\n");
    printf("\\::::::::::::::::::/    /\\::/    \\:::\\  /:::/    /\\::/    ");
    printf("\\:::\\  /:::|____|\\::/    \\:::\\  /:::|____|   /:::/~~~~/~~  ");
    printf("    \n");
    printf(" \\::::::::::::::::/____/  \\/____/ \\:::\\/:::/    /  \\/_____/");
    printf("\\:::\\/:::/    /  \\/_____/\\:::\\/:::/    /   /:::/    /      ");
    printf("   \n");
    printf("  \\:::\\~~~~\\~~~~~~                 \\::::::/    /            ");
    printf("\\::::::/    /            \\::::::/    /   /:::/    /          ");
}

static void print_title_3(void)
{
    printf("\n");
    printf("   \\:::\\    \\                       \\::::/    /             ");
    printf(" \\::::/    /              \\::::/    /   /:::/    /           ");
    printf("\n");
    printf("    \\:::\\    \\                      /:::/    /               ");
    printf(" \\::/____/                \\::/____/    \\::/    /            ");
    printf("\n");
    printf("     \\:::\\    \\                    /:::/    /                ");
    printf("  ~~                       ~~           \\/____/             \n");
    printf("      \\:::\\    \\                  /:::/    /                 ");
    printf("                                                            \n");
    printf("       \\:::\\____\\                /:::/    /                  ");
    printf("                                                            \n");
    printf("        \\::/    /                \\::/    /                    ");
    printf("                                                           \n");
    printf("         \\/____/                  \\/____/                     ");
    printf("                                                           \n\n");
    printf("----------------------------------------------------------------");
    printf("---------------------------------------------------------\n\n");
}

static void print_server_args(server_t *server)
{
    printf("Welcome to Zappy server\n");
    printf("Width: %d\n", server->arguments->x);
    printf("Height: %d\n", server->arguments->y);
    printf("Port: %d\n", server->arguments->p);
    printf("Frequency: %d\n", server->arguments->f);
    printf("Clients per team: %d\n", server->arguments->c);
    printf("Teams: ");
    for (int i = 0; server->arguments->n[i]; i++) {
        printf("%s", server->arguments->n[i]);
        if (server->arguments->n[i + 1])
            printf(", ");
    }
    printf("\n\n");
    printf("---\n\n");
    printf("Server is running on port %d\n\n", server->arguments->p);
}

void print_zappy(server_t *server)
{
    print_title_1();
    print_title_2();
    print_title_3();
    print_server_args(server);
}
