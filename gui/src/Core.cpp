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
    void Core::updateMapSize(void)
    {
        if (_world._mapX != _mapX || _world._mapY != _mapY) {
            _mapX = _world._mapX;
            _mapY = _world._mapY;
            _graphics->setMapSize(_mapX, _mapY);
        }
    }

    void Core::loop(void)
    {
        std::optional<std::string> command;

        while (_graphics->isOpen()) {
            _socket.receive(MSG_DONTWAIT);
            _graphics->update(_world);
            command = _socket.getNextCommand();
            while (command.has_value()) {
                try {
                    if (_world.handleCommand(command.value()))
                        return;
                } catch (const std::exception &e) {
                    // std::cerr << e.what() << std::endl;
                }
                command = _socket.getNextCommand();
            }
            updateMapSize();
            _graphics->render(_world);
        }
    }
} // namespace Zappy
