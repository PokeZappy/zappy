/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

#include <optional>

namespace Zappy
{
    void Sfml::handleEvent(void)
    {
        while (const std::optional<sf::Event> event = _window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                _window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            _view.move(sf::Vector2f(0.f, -_viewSpeed));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            _view.move(sf::Vector2f(0.f, _viewSpeed));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            _view.move(sf::Vector2f(-_viewSpeed, 0.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            _view.move(sf::Vector2f(_viewSpeed, 0.f));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            _view.zoom(1.05f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            _view.zoom(0.95f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            _view.rotate(sf::degrees(-2));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            _view.rotate(sf::degrees(2));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            _window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            resetViewPos();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
            _viewSpeed *= 1.05;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            _viewSpeed /= 1.05;
        }
    }
} // namespace Zappy
