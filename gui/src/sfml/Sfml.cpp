/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    Sfml::Sfml() : _window(sf::VideoMode(GUI_WIDTH, GUI_HEIGHT), "GUI") {
        _view.setSize(GUI_WIDTH, GUI_HEIGHT);
        _view.setCenter(GUI_WIDTH / 2.f, GUI_HEIGHT / 2.f);
        _font.loadFromFile("assets/Type Machine.ttf");

        _tileSelector.setFillColor(sf::Color::Transparent);
        _tileSelector.setOutlineColor(sf::Color::Red);
        _tileSelector.setOutlineThickness(3.0f);

        _tileHeight = 100;
        _tileWidth = _tileHeight;
        _tileSelector.setSize(sf::Vector2f(_tileWidth, _tileHeight));
        _tileRect.setSize(sf::Vector2f(_tileWidth, _tileHeight));

        _tileRect.setFillColor(sf::Color::Black);
        _tileRect.setOutlineColor(sf::Color::White);
        _tileRect.setOutlineThickness(3.0);

        _text.setFont(_font);
        // _text.setCharacterSize(14);
        _text.setCharacterSize(50);
        _text.setScale(0.30f, 0.30f);
        _text.setFillColor(sf::Color::White);

        _playerTriangle.setPointCount(3);
        _playerTriangle.setRadius(30);
        _playerTriangle.setFillColor(sf::Color::Green);
        _playerTriangle.setOrigin(_playerTriangle.getRadius(), _playerTriangle.getRadius());
        _playerTriangle.setScale(1, 0.5);

        _shellText.setFont(_font);
        _shellText.setCharacterSize(20);
        _shellText.setFillColor(sf::Color::White);
    };

    void Sfml::update(void)
    {
        updateMouse();
        handleEvent();

    }

    void Sfml::display(const World &world)
    {
        _window.clear();
        drawTiles(world.getTiles());
        for (auto &player : world.getPlayers()) {
            drawPlayer(player);
        }

        _window.draw(_tileSelector);
        // important de reset la view pour render tout ce qui n'est pas les tiles (overlay, text ...)
        _window.setView(_window.getDefaultView());

        drawShell(world.getShellLines());
        _window.display();
    }

    void Sfml::drawShell(const std::vector<std::string> &shellLines)
    {
        int defaultWidth = 900;
        int defaultHeight = GUI_HEIGHT - 280;
        sf::Color shellcolor = _shellText.getColor();
        shellcolor.a = 255;
        _shellText.setColor(shellcolor);
        for (auto &text : shellLines) {
            shellcolor.a -= 5;
            _shellText.setColor(shellcolor);
            _shellText.setString(text);
            _shellText.setPosition(defaultWidth, defaultHeight);
            // _shellText.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
            defaultHeight -= 20;
            _window.draw(_shellText);
        }
    }
} // namespace Zappy
