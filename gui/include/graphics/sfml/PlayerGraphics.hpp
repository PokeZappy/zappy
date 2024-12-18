/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerGraphics.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace Zappy {
    class PlayerGraphics {
    public:
        PlayerGraphics() = default;
        PlayerGraphics(sf::Color color, size_t pointCount) : color(color), pointCount(pointCount) {
            offset = {static_cast<float>(rand() % 20 - 10),
                static_cast<float>(rand() % 20 - 10)};
        }

        sf::Color color;
        sf::Vector2f offset;
        size_t pointCount;
    };
} // namespace Zappy
