/*
** EPITECH PROJECT, 2023
** gui
** File description:
** commands.cpp
*/

#include "HudMode.hpp"

namespace Zappy {
    bool HudMode::execBuiltInCommand(std::string command, std::vector<std::shared_ptr<PlayerRaylib>> &players) {
        std::istringstream iss(command);
        std::string head;
        iss >> head;
        if (head == "/follow") {
            size_t id;
            if (iss >> id) {
                std::shared_ptr<PlayerRaylib> newTarget = nullptr;
                for (auto &player : players) {
                    if (player->worldPlayer->getId() == id) {
                        newTarget = player;
                        break;
                    }
                }
                if (newTarget != nullptr)
                    _targetedPlayer = newTarget;
            }
            return (true);
        }
        return (false);
    }
}