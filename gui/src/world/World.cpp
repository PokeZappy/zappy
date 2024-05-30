/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** World.cpp
*/

#include "world/World.hpp"

namespace Zappy
{
    void World::addShellCommand(const std::string &text, std::shared_ptr<Player> player)
    {
        _shellCommands.insert(_shellCommands.begin(), ShellCommand(text, player));
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
} // namespace Zappy
