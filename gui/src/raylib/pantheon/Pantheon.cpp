/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Pantheon.cpp
*/

#include "Pantheon.hpp"
#include "PlayerRaylib.hpp"

namespace Zappy {
    void Pantheon::getPantheonPlayers(std::vector<std::shared_ptr<PlayerRaylib>> players) {
        for (auto &player : players) {
                if (player->worldPlayer->getTeam().getName() == _team && player->worldPlayer->getLevel() >= _minPantheonLevel) {
                    _players.push_back(player);
            }  
        }
    }
}