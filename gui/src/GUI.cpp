/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** zappy_gui.cpp
*/

#include "GUI.hpp"
#include "SocketExceptions.hpp"
#include <sstream>

namespace Zappy
{
    GUI::GUI()
    {
        _graphics.setWorld(&_world);
    }
    void GUI::loop(void)
    {
        std::optional<std::string> command;

        while (_graphics.isOpen()) {
            _socket.receive(MSG_DONTWAIT);
            _graphics.update();
            command = _socket.getNextCommand();
            while (command.has_value()) {
                try {
                    handleCommands(command.value());
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                command = _socket.getNextCommand();
            }
            _graphics.display();
        }
    }
} // namespace Zappy
