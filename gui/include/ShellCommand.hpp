/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ShellCommand.hpp
*/

#pragma once

#include "world/Player.hpp"
#include <optional>

namespace Zappy {
    class ShellCommand {
    public:
        ShellCommand(const std::string &text, std::shared_ptr<IEntity> entity = nullptr)
            : text(text), _entity(entity) {};
        ~ShellCommand() = default;

        const std::shared_ptr<IEntity> getEntity() const { return _entity; }

        std::string text;
    private:
        std::shared_ptr<IEntity> _entity;
    };
} // namespace Zappy
