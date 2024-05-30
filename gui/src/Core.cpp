/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Core.cpp
*/

#include "Core.hpp"
#include "SocketExceptions.hpp"
#include <sstream>

namespace Zappy
{
    void Core::loop(void)
    {
        std::optional<std::string> command;

        while (_graphics.isOpen()) {
            _socket.receive(MSG_DONTWAIT);
            _graphics.update();
            command = _socket.getNextCommand();
            while (command.has_value()) {
                try {
                    _world.handleCommand(command.value());
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                command = _socket.getNextCommand();
            }
            _graphics.display(_world);
        }
    }
} // namespace Zappy
