#pragma once

#include <SFML/Graphics.hpp>
#include "world/Color.hpp"

namespace Zappy {
    // Conversion function to sf::Color
    sf::Color toSFColor(const Color& zColor) {
        return sf::Color(zColor.r, zColor.g, zColor.b);
    }

    // inline operator sf::Color(const Color &color) {
    //     return toSFColor(color);
    // }
}
