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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            _view.move(0.f, -_viewSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _view.move(0.f, _viewSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            _view.move(-_viewSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            _view.move(_viewSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            _view.zoom(1.05f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            _view.zoom(0.95f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            _view.rotate(-2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _view.rotate(2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            resetViewPos();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            _viewSpeed *= 1.05;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            _viewSpeed /= 1.05;
        }
    }
} // namespace Zappy
