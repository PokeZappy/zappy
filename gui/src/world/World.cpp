/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** World.cpp
*/

#include "world/World.hpp"

namespace Zappy
{
    void World::initTiles(size_t width, size_t height)
    {
        _mapX = width;
        _mapY = height;
        if (_mapX == -1 || _mapY == -1 || !_tiles.empty())
            return;
        for (int height = 0; height < _mapY; height++) {
            std::vector<Tile> horizontalVector;
            for (int width = 0; width < _mapX; width++) {
                horizontalVector.push_back(Tile());
            }
            _tiles.push_back(horizontalVector);
        }
    }

    void World::updateTile(size_t x, size_t y, const Tile &tile)
    {
        if (x >= _tiles.size() || y >= _tiles[0].size())
            return;
        _tiles[y][x] = tile;
    }

    void World::updateTileInventory(size_t x, size_t y, const Inventory &inventory)
    {
        if (x >= _tiles.size() || y >= _tiles[0].size())
            return;
        _tiles[y][x].setInventory(inventory);
    }

    void World::addTeam(const std::string &teamName)
    {
        if (teamName.empty())
            return;
        for (auto &team : _teams) {
            if (team == teamName)
                return;
        }
        _teams.push_back(teamName);
    }

    std::unique_ptr<Player> & World::getPlayer(size_t id)
    {
        // for (auto &row : _tiles) {
        //     for (auto &tile : row) {
        //         for (auto &player : tile.getPlayers()) {
        //             if (player->getId() == id)
        //                 return player;
        //         }
        //     }
        // }

        // for (auto &team : _teams) {
        //     for (auto &player : team->getPlayers()) {
        //         if (player.getId() == id)
        //             return player;
        //     }
        // }
        throw std::runtime_error("Player not found");
    }
} // namespace Zappy
