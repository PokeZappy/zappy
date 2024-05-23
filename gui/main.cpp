#include "GUI.hpp"

int displayUsage(void)
{
    printf("USAGE: ./zappy_gui -p port -h machine\n");
    return (84);
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return displayUsage();
    Zappy::GUI gui;

    try {
        gui.getOptions(ac, av);
    } catch (Zappy::GUI::DoubleOptionException &e) {
        std::cerr << e.what() << std::endl;
        return displayUsage();
    } catch (Zappy::GUI::MissingOptionException &e) {
        std::cerr << e.what() << std::endl;
        return displayUsage();
    }
    catch (Zappy::GUI::InvalidOptionException &e) {
        return displayUsage();
    }
    gui.getSocket().connectSocket(gui.getPort(), gui.getMachine());
    gui.getSocket().receive();
    std::string a("GRAPHIC\n");
    gui.getSocket().sendData(a);
    return (0);
}
