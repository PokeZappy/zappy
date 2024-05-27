/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** initTiles.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    void Sfml::initTiles(size_t width, size_t height)
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
        _tileWidth = static_cast<double>(GUI_WIDTH) / _tiles[0].size();
        _tileHeight = static_cast<double>(GUI_HEIGHT) / _tiles.size();
        _tileSelector.setSize(sf::Vector2f(_tileWidth, _tileHeight));
    }
} // namespace Zappy
