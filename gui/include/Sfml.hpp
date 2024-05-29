/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Sfml.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "world/World.hpp"

namespace Zappy {
    typedef struct mouse_pos_s {
        sf::Vector2i window;
        sf::Vector2f view;
        sf::Vector2i grid;
    } mouse_pos_t;
    class Sfml {
    #define GUI_WIDTH 1920
    #define GUI_HEIGHT 1080
    public:
        Sfml();
        void update(void);
        void display(const World &world);
        bool isOpen(void) { return (_window.isOpen()); }

        void updateMouse(void);
        void handleEvent(void);

        void drawTiles(const std::vector<std::vector<Tile>> &tiles);

        void drawPlayer(const Player &player);
        void drawShell(const std::vector<std::string> &shellLines);
    private:
        sf::RenderWindow _window;
        sf::View _view;
        double _viewSpeed = 5.0f;
        sf::Font _font;
        int _mapX = -1;
        int _mapY = -1;
        double _tileWidth = -1.f;
        double _tileHeight = -1.f;
        sf::RectangleShape _tileRect;
        sf::RectangleShape _tileSelector;
        sf::Text _text;
        mouse_pos_t _mousePositions;
        sf::CircleShape _playerTriangle;
        sf::Text _shellText;
    };

} // namespace Zappy
