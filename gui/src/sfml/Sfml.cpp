/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    Sfml::Sfml(World *world) : _window(sf::VideoMode(GUI_WIDTH, GUI_HEIGHT), "GUI"), _world(world) {
        _view.setSize(GUI_WIDTH, GUI_HEIGHT);
        _view.setCenter(GUI_WIDTH / 2.f, GUI_HEIGHT / 2.f);
        _font.loadFromFile("assets/Type Machine.ttf");

        _tileSelector.setFillColor(sf::Color::Transparent);
        _tileSelector.setOutlineColor(sf::Color::Red);
        _tileSelector.setOutlineThickness(3.0f);

        _tileRect.setFillColor(sf::Color::Black);
        _tileRect.setOutlineColor(sf::Color::White);
        _tileRect.setOutlineThickness(3.0);

        _text.setFont(_font);
        _text.setCharacterSize(100);
        _text.setScale(0.2f, 0.2f);
        _text.setFillColor(sf::Color::White);
    };

    void Sfml::update(void)
    {
        updateMouse();
        handleEvent();
    }

    void Sfml::display(void)
    {
        _window.clear();
        drawTiles();

        // if (!_tiles.empty())
        _window.draw(_tileSelector);
        // important de reset la view pour render tout ce qui n'est pas les tiles (overlay, text ...)
        _window.setView(_window.getDefaultView());
        _window.display();
    }
} // namespace Zappy
