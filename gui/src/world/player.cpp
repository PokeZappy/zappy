/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** World.cpp
*/

#include "world/World.hpp"

namespace Zappy
{
    std::shared_ptr<Player> World::getPlayer(size_t id)
    {
        for (auto player : _players) {
            if (player->getId() == id)
                return player;
        }
        throw std::runtime_error("Player not found");
    }

    std::vector<std::shared_ptr<Player>> World::getPlayers(size_t x, size_t y)
    {
        std::vector<std::shared_ptr<Player>> players;
        for (auto player : _players) {
            if (player->getX() == x && player->getY() == y)
                players.push_back(player);
        }
        return players;
    }

    void World::killPlayer(size_t id)
    {
        for (auto it = _players.begin(); it != _players.end(); it++) {
            if ((*it)->getId() == id) {
                _players.erase(it);
                return;
            }
        }
    }
} // namespace Zappy
