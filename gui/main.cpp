#include "Core.hpp"
#include "SocketExceptions.hpp"

int displayUsage(void)
{
    printf("USAGE: ./zappy_gui -p port -h machine\n");
    return (84);
}


// Custom logging funtion
void LogColored(int msgType, const char *text, va_list args)
{
	switch (msgType)
	{
		case LOG_INFO: printf("[\e[1;32mINFO\e[0m] : "); break;
		case LOG_ERROR: printf("[\e[1;31mERROR\e[0m]: "); break;
		case LOG_WARNING: printf("[\e[1;33mWARN\e[0m] : "); break;
		case LOG_DEBUG: printf("[DEBUG]: "); break;
		default: break;
	}

	vprintf(text, args);
	printf("\n");
}

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return displayUsage();
    SetTraceLogCallback(LogColored);
    SetTraceLogLevel(LOG_WARNING);
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
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    core.loop();
    return (0);
}
