/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile.cpp
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
                horizontalVector.push_back(Tile(height, width));
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
} // namespace Zappy
