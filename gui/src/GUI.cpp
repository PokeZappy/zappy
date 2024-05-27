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
    GUI::GUI(void)
    {
    }

    void GUI::handleCommands(std::string &line)
    {
        int commandPos = line.find(' ');
        std::string command = line.substr(0, commandPos);
        std::string args = line.substr(commandPos + 1);
        std::istringstream ss(args);

        size_t x, y;

        if (command == "msz") {
            ss >> x >> y;
            _graphics.initTiles(x, y);
        }
        if (command == "bct") {
            ss >> x >> y;
            Tile tile(ss);
            _graphics.updateTile(x, y, tile);
        }
        if (command == "tna") {
            std::string teamName;
            ss >> teamName;
            if (teamName.empty())
                return;
            for (auto &team : _teams) {
                if (team == teamName)
                    return;
            }
            _teams.push_back(teamName);
        }
    }

    void GUI::loop(void)
    {
        std::optional<std::string> command;

        while (_graphics.isOpen()) {
            _socket.receive(MSG_DONTWAIT);
            _graphics.update();
            command = _socket.getNextCommand();
            while (command.has_value()) {
                handleCommands(command.value());
                command = _socket.getNextCommand();
            }
            _graphics.display();
        }
    }
} // namespace Zappy
