/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tiles.cpp
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
        _tileRect.setSize(sf::Vector2f(_tileWidth, _tileHeight));
    }

    void Sfml::drawTiles(void)
    {
        if (_tiles.empty())
            return;

        for (size_t height = 0; height < _tiles.size(); height++) {
            for (size_t width = 0; width < _tiles[height].size(); width++) {
                _tileRect.setPosition(width * _tileWidth, height * _tileHeight);
                _window.draw(_tileRect);
                for (size_t i = 0; i < 7; i++) {
                    _text.setString(std::to_string(_tiles[height][width].getItem(i)));
                    _text.setPosition(width * _tileWidth + 10 + (i / 4) * _tileWidth / 2,
                        height * _tileHeight + (i % 4) * 20);
                    _window.draw(_text);
                }
            }
        }
    }

    void Sfml::updateTile(size_t x, size_t y, Tile tile)
    {
        if (x >= _tiles.size() || y >= _tiles[0].size())
            return;
        _tiles[y][x] = tile;
    }
} // namespace Zappy
