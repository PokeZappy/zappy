/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tiles.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    void Sfml::drawTiles(const std::vector<std::vector<Tile>> &tiles)
    {
        for (size_t height = 0; height < tiles.size(); height++) {
            for (size_t width = 0; width < tiles[height].size(); width++) {
                _tileRect.setPosition(width * _tileWidth, height * _tileHeight);
                _window.draw(_tileRect);
                for (size_t i = 0; i < 7; i++) {
                    _resourcesText.setString(std::to_string(tiles[height][width].getItem(i)));
                    _resourcesText.setPosition(width * _tileWidth + 10,
                        height * _tileHeight + i * 13);
                    _resourcesText.setFillColor(getItemColor(static_cast<Item>(i)));
                    _window.draw(_resourcesText);
                }
            }
        }
    }

    void Sfml::drawPlayer(const std::shared_ptr<Player> player)
    {
        sf::Vector2f tileCenter(player->getX() * _tileWidth + _tileWidth / 2,
            player->getY() * _tileHeight + _tileHeight / 2);
        _playerTriangle.setPosition(tileCenter);
        // _playerTriangle.setRotation(90 * 0);
        // _playerTriangle.setRotation((player->getOrientation() - 1) * 90);
        switch (player->getOrientation()) {
        case Orientation::NORTH: _playerTriangle.setRotation(180); break;
        case Orientation::EAST: _playerTriangle.setRotation(90); break;
        case Orientation::SOUTH: _playerTriangle.setRotation(0); break;
        case Orientation::WEST: _playerTriangle.setRotation(270); break;
        default:
            break;
        }
        _playerTriangle.setFillColor(getTeamColor(player->getTeam().getType()));
        _playerTriangle.setOutlineColor(getPlayerColor(player));
        _playerLevelText.setString(std::to_string(player->getLevel()));
        _playerLevelText.setPosition(tileCenter - sf::Vector2f(5, 10));
        _window.draw(_playerTriangle);
        _window.draw(_playerLevelText);
    }
} // namespace Zappy
