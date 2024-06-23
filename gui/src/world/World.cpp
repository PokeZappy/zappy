/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** World.cpp
*/

#include "world/World.hpp"

namespace Zappy
{
    void World::addShellCommand(const std::string &text, std::shared_ptr<IEntity> entity)
    {
        _shellCommands.insert(_shellCommands.begin(), ShellCommand(text, entity));
        if (_shellCommands.size() > 42)
            _shellCommands.pop_back();
    }

    const std::vector<ShellCommand> &World::getShellCommands(void) const
    {
        // I would like to scroll to see the previouses commands but it segfaults
        // std::vector<ShellCommand> commands;
        // size_t index = 0;
        // commands.push_back(ShellCommand("test", nullptr));
        // for (auto &command : _shellCommands) {
        //     // for (size_t i = 0; i < _shellOffset; i++) {
        //     //     continue;
        //     // }
        //     commands.push_back(command);
        //     // if (index >= 30)
        //     //     break;
        //     index++;
        // }
        // return commands;
        return _shellCommands;
    }

    std::string World::getOrientationString(Orientation orientation) {
        switch (orientation) {
            case Orientation::NORTH: return "NORTH";
            case Orientation::EAST: return "EAST";
            case Orientation::SOUTH: return "SOUTH";
            case Orientation::WEST: return "WEST";
            default: return "NONE";
        }
    }

    std::string World::getItemString(Item item) {
        switch (item) {
            case Item::FOOD: return "food";
            case Item::LINEMATE: return "linemate";
            case Item::DERAUMERE: return "deraumere";
            case Item::SIBUR: return "sibur";
            case Item::MENDIANE: return "mendiane";
            case Item::PHIRAS: return "phiras";
            case Item::THYSTAME: return "thystame";
            default: return "none";
        }
    }

    std::shared_ptr<Egg> World::getEgg(size_t id)
    {
        for (auto egg : _eggs) {
            if (egg->getId() == id)
                return egg;
        }
        throw std::runtime_error("Egg not found");
    }

    bool World::containsPlayer(size_t id) const
    {
        for (auto player : _players) {
            if (player->getId() == id)
                return true;
        }
        return false;
    }

    bool World::containsEgg(size_t id) const
    {
        for (auto egg : _eggs) {
            if (egg->getId() == id)
                return true;
        }
        return false;
    }
} // namespace Zappy
