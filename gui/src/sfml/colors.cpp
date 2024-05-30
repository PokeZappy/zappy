/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** colors.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    sf::Color Sfml::getTeamColor(TeamType teamType) {
        switch (teamType) {
        case TeamType::FIRE:
            return sf::Color::Red;
        case TeamType::GRASS:
            return sf::Color::Green;
        case TeamType::WATER:
            return sf::Color::Blue;
        default:
            return sf::Color::White;
        }
    }

    sf::Color Sfml::getTextColor(const ShellCommand &command)
    {
        auto entity = command.getEntity();
        if (entity != nullptr) {
            return getTeamColor(entity->getTeam().getType());
        }
        return sf::Color::White;
    }

    sf::Color Sfml::getEntityColor(const std::shared_ptr<IEntity> entity)
    {
        size_t playerId = entity->getId();
        if (_playersGraphics.contains(playerId)) {
            // if (player->isIncanting()) {
            //     return sf::Color(rand() % 255, rand() % 255, rand() % 255);
            // }
            return _playersGraphics[playerId].color;
        }
        sf::Color color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
        _playersGraphics[playerId] = PlayerGraphics(color);
        return color;
    }

    sf::Color Sfml::getItemColor(Item itemType)
    {
        switch (itemType) {
        case Item::FOOD: return sf::Color::Red;
        case Item::LINEMATE: return sf::Color::Yellow;
        case Item::DERAUMERE: return sf::Color::Cyan;
        case Item::SIBUR: return sf::Color::Magenta;
        case Item::MENDIANE: return sf::Color::Green;
        case Item::PHIRAS: return sf::Color::Blue;
        case Item::THYSTAME: return sf::Color::White;
        }
    }

} // namespace Zappy
