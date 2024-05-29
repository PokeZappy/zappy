/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tiles.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    void Sfml::initTiles(const std::vector<std::vector<Tile>> &tiles)
    {
        _tileHeight = 100;
        _tileWidth = _tileHeight;
        _tileSelector.setSize(sf::Vector2f(_tileWidth, _tileHeight));
        _tileRect.setSize(sf::Vector2f(_tileWidth, _tileHeight));
    }

    void Sfml::drawTiles(void)
    {
        auto tiles = _world->getTiles();
        for (size_t height = 0; height < tiles.size(); height++) {
            for (size_t width = 0; width < tiles[height].size(); width++) {
                _tileRect.setPosition(width * _tileWidth, height * _tileHeight);
                _window.draw(_tileRect);
                for (size_t i = 0; i < 7; i++) {
                    _text.setString(std::to_string(tiles[height][width].getItem(i)));
                    _text.setPosition(width * _tileWidth + 10 + (i / 4) * _tileWidth / 2,
                        height * _tileHeight + (i % 4) * 20);
                    _window.draw(_text);
                }
            }
        }
    }
} // namespace Zappy
