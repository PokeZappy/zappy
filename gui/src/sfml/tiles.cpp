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

    void Sfml::drawEntity(const std::shared_ptr<IEntity> entity)
    {
        sf::Vector2f tileCenter(entity->getX() * _tileWidth + _tileWidth / 2,
            entity->getY() * _tileHeight + _tileHeight / 2);
        _entityTriangle.setPosition(tileCenter + getEntityOffset(entity));
        _entityTriangle.setPointCount(getEntityPointCount(entity));
        _entityTriangle.setRotation(90);
        if (entity->getType() == EntityType::PLAYER) {
            Player *player = static_cast<Player *>(entity.get());
            // _entityTriangle.setRotation((player->getOrientation() - 1) * 90);
            switch (player->getOrientation()) {
            case Orientation::NORTH: _entityTriangle.setRotation(180); break;
            case Orientation::EAST: _entityTriangle.setRotation(90); break;
            case Orientation::SOUTH: _entityTriangle.setRotation(0); break;
            case Orientation::WEST: _entityTriangle.setRotation(270); break;
            default:
                break;
            }
        }
        _entityTriangle.setFillColor(getTeamColor(entity->getTeam().getType()));
        _entityTriangle.setOutlineColor(getEntityColor(entity));
        _window.draw(_entityTriangle);
        if (entity->getType() == EntityType::PLAYER) {
            Player *player = static_cast<Player *>(entity.get());
            _playerLevelText.setString(std::to_string(player->getLevel()));
            _playerLevelText.setPosition(tileCenter - sf::Vector2f(5, 10) + getEntityOffset(entity));
            _window.draw(_playerLevelText);
        }
    }
} // namespace Zappy
