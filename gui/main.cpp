#include "zappy_gui.hpp"

int displayUsage(void)
{
    printf("USAGE: ./zappy_gui -p port -h machine\n");
    return (84);
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return displayUsage();
    ZappyGUI gui;

    try {
        gui.getOptions(ac, av);
    } catch (...) {
        return displayUsage();
    }
    return (0);
}
