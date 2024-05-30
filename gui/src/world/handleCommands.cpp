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

        if (commandName != "bct" && commandName != "ppo" && commandName != "pin" && commandName != "pgt") {
            std::cout << command << std::endl;
        }
        // if (commandName == "ebo" || commandName == "enw" || commandName == "pfk")
        //     std::cout << command << std::endl;
        // }

        if (commandName == "msz") { // map size
            ss >> x >> y;
            initTiles(x, y);
            addShellCommand("Map size : x " + std::to_string(x) + ", y " + std::to_string(y));
        }
        else if (commandName == "bct") { // content of a tile
            ss >> x >> y;
            Inventory inventory(ss);
            updateTileInventory(x, y, inventory);
        }
        else if (commandName == "tna") { // name of all the teams
            std::string teamName;
            ss >> teamName;
            addTeam(teamName);
        }
        else if (commandName == "pnw") { // connection of a new player
            size_t orientation, level;
            std::string teamName;
            ss >> id >> x >> y >> orientation >> level >> teamName;
            std::shared_ptr<Player> player = std::make_shared<Player>(id, x, y,
                static_cast<Orientation>(orientation), level, getTeam(teamName));
            // player->setIncanting(true);
            addPlayer(player);
            addShellCommand("New player T" + std::to_string(id) + " joined the game", player);
        }
        else if (commandName == "ppo") { // player’s position
            size_t o;
            ss >> id >> x >> y >> o;
            Orientation orientation = static_cast<Orientation>(o);
            std::shared_ptr<Player> player = getPlayer(id);
            player->setPos(x, y, orientation);

            // addShellCommand("T" + std::to_string(id) + " moved to {x: " +
            //     std::to_string(x) + ", y: " + std::to_string(y) + ", o: " +
            //     getOrientationString(orientation) + "}", player);
        }
        else if (commandName == "plv") { // player’s level
            size_t level;
            ss >> level;
            std::shared_ptr<Player> player = getPlayer(id);
            player->setLevel(level);
            addShellCommand("T" + std::to_string(id) + " is now level " +
                std::to_string(level), player);
        }
        else if (commandName == "pin") { // player’s inventory
            ss >> id;
            Inventory inventory(ss);
            getPlayer(id)->setInventory(inventory);
        }
        else if (commandName == "pex") { // expulsion

        }
        else if (commandName == "pbc") { // broadcast
            std::string message;
            ss >> id >> message;
            addShellCommand("T" + std::to_string(id) + " says: " + message, getPlayer(id));
        }
        else if (commandName == "pic") { // start of an incantation (by the first player)
            ss >> x >> y >> id;
            getPlayer(id)->setIncanting(true);
            addShellCommand("Incantation started at {x: " + std::to_string(x) + ", y: " +
                std::to_string(y) + "} by T" + std::to_string(id), getPlayer(id));
        }
        else if (commandName == "pie") { // end of an incantation
            std::string result;
            ss >> x >> y >> result;
            if (result == "ok") {
                for (auto player : getPlayers(x, y)) {
                    player->setIncanting(false);
                }
                addShellCommand("Incantation at {x: " + std::to_string(x) + ", y: " +
                    std::to_string(y) + "} succeeded", getPlayer(id));
            }
            else
                addShellCommand("Incantation at {x: " + std::to_string(x) + ", y: " +
                    std::to_string(y) + "} failed", getPlayer(id));
            std::cout << command << std::endl;
        }
        else if (commandName == "pfk") { // egg laying by the player

        }
        else if (commandName == "pdr") { // resource dropping

        }
        else if (commandName == "pgt") { // resource collecting

        }
        else if (commandName == "pdi") { // death of a player
            ss >> id;
            addShellCommand("T" + std::to_string(id) + " died", getPlayer(id));
            killPlayer(id);
        }
        else if (commandName == "enw") {
            int idPlayer;
            ss >> id >> idPlayer >> x >> y;
            std::shared_ptr<Egg> egg;
            if (idPlayer < 0)
                egg = std::make_shared<Egg>(id, idPlayer, x, y, defaultTeam);
            else
                egg = std::make_shared<Egg>(id, idPlayer, x, y, getPlayer(idPlayer)->getTeam());
            addEgg(egg);
            addShellCommand("New egg E" + std::to_string(id) + " laid by player",
                getEgg(id));
        }
        else if (commandName == "ebo") { // player connection for an egg

        }
        else if (commandName == "edi") { // death of an egg

        }
        else if (commandName == "sgt") { // time unit request

        }
        else if (commandName == "sst") { // time unit modification

        }
        else if (commandName == "seg") { // end of game

        }
        else if (commandName == "smg") { // message from the server
            std::string message;
            ss >> message;
            addShellCommand("Server : " + message);
        }
        else if (commandName == "suc") { // unknown command

        }
        else if (commandName == "sbp") { // command parameter

        }
        else if (commandName == "eht") {
            // DEPRECATED
        }
        else {
            // std::cerr << "Unknown command: " << command.substr(0, command.size() - 2) << std::endl;
        }
    }
} // namespace Zappy
