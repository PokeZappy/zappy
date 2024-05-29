#include "Core.hpp"

int displayUsage(void)
{
    printf("USAGE: ./zappy_gui -p port -h machine\n");
    return (84);
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return displayUsage();
    Zappy::Core core;

    try {
        core.getOptions(ac, av);
    } catch (Zappy::Core::DoubleOptionException &e) {
        std::cerr << e.what() << std::endl;
        return displayUsage();
    } catch (Zappy::Core::MissingOptionException &e) {
        std::cerr << e.what() << std::endl;
        return displayUsage();
    }
    catch (Zappy::Core::InvalidOptionException &e) {
        return displayUsage();
    }
    core.getSocket().connectSocket(core.getPort(), core.getMachine());
    core.loop();
    return (0);
}
