/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handleCommand.cpp
*/

#include "world/World.hpp"

namespace Zappy
{
    namespace {
        // The Zappy protocol prefixes entity ids with '#' ("pnw #42 2 3 1 1 team").
        // Extracting one straight into an integer stops on the '#', which leaves the
        // value at 0 and latches failbit on the stream, so every later extraction of
        // the same command silently fails too. Servers that omit the '#' still work.
        long long parseId(std::istream &is)
        {
            std::string token;

            if (!(is >> token))
                return -1;
            if (!token.empty() && token.front() == '#')
                token.erase(0, 1);
            try {
                return std::stoll(token);
            } catch (const std::exception &) {
                is.setstate(std::ios::failbit);
                return -1;
            }
        }
    }

    bool World::handleCommand(std::string &command)
    {
        int commandPos = command.find(' ');
        std::string commandName = command.substr(0, commandPos);
        std::string args = command.substr(commandPos + 1);
        std::istringstream ss(args);

        size_t x, y, id = 0;

        // if (commandName != "bct" && commandName != "ppo" && commandName != "pin" && commandName != "pgt") {
        //     std::cout << command << std::endl;
        // }
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
            id = parseId(ss);
            ss >> x >> y >> orientation >> level >> teamName;
            std::shared_ptr<Player> player = std::make_shared<Player>(id, x, y,
                static_cast<Orientation>(orientation), level, getTeam(teamName));
            addPlayer(player);
            addShellCommand("New player T" + std::to_string(id) + " joined the game", player);
        }
        else if (commandName == "ppo") { // player’s position
            size_t o;
            id = parseId(ss);
            ss >> x >> y >> o;
            Orientation orientation = static_cast<Orientation>(o);
            std::shared_ptr<Player> player = getPlayer(id);
            player->setPos(x, y);
            player->setOrientation(orientation);

            //? info : Uncomment to have player movements in the shell
            // addShellCommand("T" + std::to_string(id) + " moved to {x: " +
            //     std::to_string(x) + ", y: " + std::to_string(y) + ", o: " +
            //     getOrientationString(orientation) + "}", player);
        }
        else if (commandName == "plv") { // player’s level
            size_t level;
            id = parseId(ss);
            ss >> level;
            std::shared_ptr<Player> player = getPlayer(id);
            player->setLevel(level);
            addShellCommand("T" + std::to_string(id) + " is now level " +
                std::to_string(level), player);
        }
        else if (commandName == "pin") { // player’s inventory
            id = parseId(ss);
            ss >> x >> y;
            Inventory inventory(ss);
            getPlayer(id)->setInventory(inventory);
        }
        else if (commandName == "pex") { // expulsion
            id = parseId(ss);
            std::shared_ptr<Player> player = getPlayer(id);
            player->setPush(true);
            for (auto player : getPlayers(player->getX(), player->getY())) {
                if (player->getIncantationState() == Incantation::INCANTING)
                    player->setIncanting(Incantation::FAILURE);
            }
            addShellCommand("T" + std::to_string(id) + " pushes everyone on his tile", getPlayer(id));
        }
        else if (commandName == "pbc") { // broadcast
            std::string message;
            id = parseId(ss);
            std::getline(ss, message);
            // the payload is the rest of the line, sent between double quotes
            size_t start = message.find_first_not_of(' ');
            message = (start == std::string::npos) ? "" : message.substr(start);
            if (message.size() >= 2 && message.front() == '"' && message.back() == '"')
                message = message.substr(1, message.size() - 2);
            getPlayer(id)->setBroadcast(message);
            addShellCommand("T" + std::to_string(id) + " says: " + message, getPlayer(id));
        }
        else if (commandName == "pic") { // start of an incantation (by the first player)
            size_t level;
            std::string colleagues;
            ss >> x >> y >> level;
            id = parseId(ss);
            getPlayer(id)->setIncanting(Incantation::INCANTING);
            for (long long otherId = parseId(ss); otherId >= 0;
                otherId = parseId(ss)) {
                getPlayer(otherId)->setIncanting(Incantation::INCANTING);
                colleagues += ", T" + std::to_string(otherId);
            }

            addShellCommand("Incantation started of level " + std::to_string(level) +
                " at {x: " + std::to_string(x) + ", y: " +
                std::to_string(y) + "} by T" + std::to_string(id) + (colleagues.empty() ? "" : " with his colleagues") +
                colleagues, getPlayer(id));
        }
        else if (commandName == "pie") { // end of an incantation
            std::string result;
            ss >> x >> y >> result;

            try {
                size_t value = std::stoull(result);
                if (value >= 1 && value <= 8) {
                    // "pie X Y R" carries no player id, so none can be attached here
                    addShellCommand("Incantation at {x: " + std::to_string(x) + ", y: " +
                        std::to_string(y) + "} succeeded");
                        for (auto player : getPlayers(x, y)) {
                            if (player->getIncantationState() == Incantation::INCANTING)
                                player->setIncanting(Incantation::SUCCESS);
                        }
                } else {
                    throw std::out_of_range("The number is out of range for size_t.");
                }
            } catch (const std::exception& e) {
                addShellCommand("Incantation at {x: " + std::to_string(x) + ", y: " +
                    std::to_string(y) + "} failed");
                for (auto player : getPlayers(x, y)) {
                    if (player->getIncantationState() == Incantation::INCANTING)
                        player->setIncanting(Incantation::FAILURE);
                }
            }
        }
        else if (commandName == "pfk") { // egg laying by the player

        }
        else if (commandName == "pdr") { // resource dropping
            size_t item;
            id = parseId(ss);
            ss >> item;
            //? info : Uncomment this to show the player dropped items in the shell
            // addShellCommand("T" + std::to_string(id) + " dropped " + getItemString(static_cast<Item>(item)),
            //     getPlayer(id));
        }
        else if (commandName == "pgt") { // resource collecting
            size_t item;
            id = parseId(ss);
            ss >> item;
            //? info : Uncomment this to show the player collected items in the shell
            // addShellCommand("T" + std::to_string(id) + " collected " + getItemString(static_cast<Item>(item)),
            //     getPlayer(id));
        }
        else if (commandName == "pdi") { // death of a player
            id = parseId(ss);
            addShellCommand("T" + std::to_string(id) + " died", getPlayer(id));
            killPlayer(id);
        }
        else if (commandName == "enw") { // an egg was laid by a player
            long long idPlayer;
            id = parseId(ss);
            idPlayer = parseId(ss);
            ss >> x >> y;
            std::shared_ptr<Egg> egg;
            if (idPlayer < 0)
                egg = std::make_shared<Egg>(id, idPlayer, x, y, defaultTeam);
            else
                egg = std::make_shared<Egg>(id, idPlayer, x, y, getPlayer(idPlayer)->getTeam());
            addEgg(egg);
            addShellCommand("New egg E" + std::to_string(id) + " laid by player T" + std::to_string(idPlayer),
                getEgg(id));
        }
        else if (commandName == "ebo") { // player connection for an egg
            id = parseId(ss);
            addShellCommand("Player connected to egg E" + std::to_string(id),
                getEgg(id));
            killEgg(id);
        }
        else if (commandName == "edi") { // death of an egg
            id = parseId(ss);
            addShellCommand("E" + std::to_string(id) + " died", getEgg(id));
            killEgg(id);
        }
        else if (commandName == "sgt") { // time unit request

        }
        else if (commandName == "sst") { // time unit modification

        }
        else if (commandName == "seg") { // end of game
            addShellCommand("Game ended");
            ss >> _winningTeam;
            std::cout << "Game ended" << std::endl;
            // return true;
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
        return false;
    }
} // namespace Zappy
