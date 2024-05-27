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

#include "World.hpp"

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
        Sfml(World *world = nullptr);
        void update(void);
        void display(void);
        bool isOpen(void) { return (_window.isOpen()); }

        void setWorld(World *world) { _world = world; }

        void updateMouse(void);
        void handleEvent(void);

        void drawTiles(void);
        void initTiles(const std::vector<std::vector<Tile>> &tiles);
    private:
        sf::RenderWindow _window;
        sf::View _view;
        double _viewSpeed = 5.0f;
        sf::Font _font;
        World *_world;
        int _mapX = -1;
        int _mapY = -1;
        double _tileWidth = -1.f;
        double _tileHeight = -1.f;
        sf::RectangleShape _tileRect;
        sf::RectangleShape _tileSelector;
        sf::Text _text;
        mouse_pos_t _mousePositions;
    };

} // namespace Zappy
