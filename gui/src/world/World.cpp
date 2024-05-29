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
            if (team.getName() == teamName)
                return;
        }
        _teams.push_back(Team(teamName));
    }

    Team &World::getTeam(const std::string &teamName)
    {
        for (auto &team : _teams) {
            if (team.getName() == teamName)
                return team;
        }
        throw std::runtime_error("Team not found");
    }

    Player &World::getPlayer(size_t id)
    {
        for (auto &player : _players) {
            if (player.getId() == id)
                return player;
        }
        throw std::runtime_error("Player not found");
    }

    void World::addShellLine(const std::string &line)
    {
        _shellLines.insert(_shellLines.begin(), line);
        if (_shellLines.size() > 42)
            _shellLines.pop_back();
    }
} // namespace Zappy
