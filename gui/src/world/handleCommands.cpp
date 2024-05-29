/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handleCommand.cpp
*/

#include "world/World.hpp"

namespace Zappy
{
    void World::handleCommand(std::string &command)
    {
        int commandPos = command.find(' ');
        std::string commandName = command.substr(0, commandPos);
        std::string args = command.substr(commandPos + 1);
        std::istringstream ss(args);

        size_t x, y, id = 0;

        // std::cout << "Command: " << commandName << std::endl;

        if (commandName == "msz") {
            ss >> x >> y;
            initTiles(x, y);
            addShellLine("Map size : x " + std::to_string(x) + ", y " + std::to_string(y));
        }
        else if (commandName == "bct") {
            ss >> x >> y;
            Inventory inventory(ss);
            updateTileInventory(x, y, inventory);
        }
        else if (commandName == "tna") {
            std::string teamName;
            ss >> teamName;
            addTeam(teamName);
        }
        else if (commandName == "pnw") {
            size_t orientation, level;
            std::string teamName;
            ss >> id >> x >> y >> orientation >> level >> teamName;
            Player player = Player(id, x, y, static_cast<Orientation>(orientation),
                level, getTeam(teamName));
            addPlayer(player);
            addShellLine("New player T" + std::to_string(id) + " joined the game");
        }
        else if (commandName == "ppo") {
            size_t o;
            ss >> id >> x >> y >> o;
            Orientation orientation = static_cast<Orientation>(o);
            getPlayer(id).setPos(x, y, orientation);

            addShellLine("T" + std::to_string(id) + " moved to {x: " +
                std::to_string(x) + ", y: " + std::to_string(y) + ", o: " +
                getOrientationString(orientation) + "}");
        }
        else if (commandName == "plv") {
            size_t level;
            ss >> level;
            getPlayer(id).setLevel(level);
            addShellLine("T" + std::to_string(id) + " is now level " + std::to_string(level));
        }
        else if (commandName == "pin") {
            ss >> id;
            Inventory inventory(ss);
            getPlayer(id).setInventory(inventory);
        }
        else if (commandName == "pex") {

        }
        else if (commandName == "pbc") {
            std::string message;
            ss >> id >> message;
            addShellLine("T" + std::to_string(id) + " says: " + message);
        }
        else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
} // namespace Zappy
