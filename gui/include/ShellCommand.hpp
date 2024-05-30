/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ShellCommand.hpp
*/

#pragma once

#include "Tools.hpp"
#include "world/Player.hpp"
#include <optional>

namespace Zappy {
    class ShellCommand {
    public:
        ShellCommand(const std::string &text, std::shared_ptr<Player> player = nullptr)
            : text(text), _player(player) {};
        ~ShellCommand() = default;

        const std::shared_ptr<Player> getPlayer() const { return _player; }

        std::string text;
    private:
        std::shared_ptr<Player> _player;
    };
} // namespace Zappy
