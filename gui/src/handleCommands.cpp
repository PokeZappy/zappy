/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handleCommands.cpp
*/

#include "GUI.hpp"

namespace Zappy
{
    void GUI::handleCommands(std::string &line)
    {
        int commandPos = line.find(' ');
        std::string command = line.substr(0, commandPos);
        std::string args = line.substr(commandPos + 1);
        std::istringstream ss(args);

        size_t x, y, id = 0;

        // std::cout << "Command: " << command << std::endl;

        if (command == "msz") {
            ss >> x >> y;
            _world.initTiles(x, y);
            _graphics.initTiles(_world.getTiles());
        }
        else if (command == "bct") {
            ss >> x >> y;
            Inventory inventory(ss);
            _world.updateTileInventory(x, y, inventory);
        }
        else if (command == "tna") {
            std::string teamName;
            ss >> teamName;
            _world.addTeam(teamName);
        }
        else if (command == "pnw") {
            std::unique_ptr<Player> player = std::make_unique<Player>(ss);
            // _world.addPlayer(player);
        }
        else if (command == "ppo") {
            size_t orientation;
            ss >> id >> x >> y >> orientation;
            _world.getPlayer(id)->setPos(x, y, static_cast<Orientation>(orientation));
        }
        else if (command == "plv") {
            size_t level;
            ss >> level;
            _world.getPlayer(id)->setLevel(level);
        }
        else if (command == "pin") {
            ss >> id;
            Inventory inventory(ss);
            _world.getPlayer(id)->setInventory(inventory);
        }
        else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
} // namespace Zappy
