
#pragma once
namespace sf {
    class Color;
}

// ZappyColor.h
namespace Zappy {
    class Color {
    private:
        int r;
        int g;
        int b;

    public:
        // Default constructor
        Color() : r(255), g(255), b(255) {}  // Default to white

        // Constructor from RGB values
        Color(int red, int green, int blue) 
            : r(red), g(green), b(blue) {}

        // Getters for r, g, and b
        int getRed() const { return r; }
        int getGreen() const { return g; }
        int getBlue() const { return b; }

        // Friend function for conversion to sf::Color
        friend sf::Color toSFColor(const Color &zColor);
    };
}
