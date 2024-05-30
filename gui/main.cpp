#include "Core.hpp"
#include "SocketExceptions.hpp"

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
    try {
        core.getSocket().connectSocket(core.getPort(), core.getMachine());
    } catch (ServerConnectionException &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    } catch (SocketException &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    core.loop();
    return (0);
}
