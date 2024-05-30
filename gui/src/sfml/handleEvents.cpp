/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

namespace Zappy
{
    void Sfml::handleEvent(void)
    {
        sf::Event event;

        while (_window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed):
                    _window.close();
                    break;
                default: break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            _view.move(0.f, -_viewSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _view.move(0.f, _viewSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            _view.move(-_viewSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            _view.move(_viewSpeed, 0.f);
        }
    }
} // namespace Zappy
