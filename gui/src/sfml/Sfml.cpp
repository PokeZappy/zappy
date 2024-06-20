/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Sfml.cpp
*/

#include "Sfml.hpp"

#include <filesystem>

namespace Zappy
{
    Sfml::Sfml() : _window(sf::VideoMode(GUI_WIDTH, GUI_HEIGHT), "GUI") {
        resetViewPos();
        _window.setFramerateLimit(60);
        if (std::filesystem::exists("assets"))
            _font.loadFromFile("assets/Type Machine.ttf");
        else if (std::filesystem::exists("gui/assets"))
            _font.loadFromFile("gui/assets/Type Machine.ttf");
        else
            throw std::runtime_error("Assets not found");

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

        _resourcesText.setFont(_font);
        // _resourcesText.setCharacterSize(14);
        _resourcesText.setCharacterSize(50);
        _resourcesText.setScale(0.30f, 0.30f);
        _resourcesText.setFillColor(sf::Color::White);
        _resourcesText.setStyle(sf::Text::Bold);

        _entityTriangle.setPointCount(3);
        _entityTriangle.setRadius(25);
        _entityTriangle.setFillColor(sf::Color::Green);
        _entityTriangle.setOrigin(_entityTriangle.getRadius(), _entityTriangle.getRadius());
        _entityTriangle.setOutlineThickness(8);
        _entityTriangle.setScale(1, 0.5);

        _playerLevelText.setFont(_font);
        _playerLevelText.setCharacterSize(20);
        _playerLevelText.setFillColor(sf::Color::White);
        _playerLevelText.setOutlineThickness(2);
        _playerLevelText.setOutlineColor(sf::Color::Black);

        _shellText.setFont(_font);
        _shellText.setCharacterSize(20);
        _shellText.setFillColor(sf::Color::White);

        _shellTextTeamColor.setSize(sf::Vector2f(15, 15));
    };

    void Sfml::update(const World &world)
    {
        _mapX = world._mapX;
        _mapY = world._mapY;
        updateMouse();
        handleEvent();
    }

    void Sfml::render(const World &world)
    {
        _window.clear();
        drawTiles(world.getTiles());
        for (auto &egg : world.getEggs()) {
            drawEntity(egg);
        }
        for (auto &player : world.getPlayers()) {
            drawEntity(player);
        }

        _window.draw(_tileSelector);
        // important de reset la view pour render tout ce qui n'est pas les tiles (overlay, text ...)
        _window.setView(_window.getDefaultView());
        drawShell(world.getShellCommands());
        _window.display();
    }

    sf::Vector2f Sfml::getEntityOffset(const std::shared_ptr<IEntity> entity)
    {
        for (auto &playerGraphics : _entityGraphics) {
            if (playerGraphics.first.first != entity->getType() &&
            playerGraphics.first.second != entity->getId())
                continue;
            return playerGraphics.second.offset;
        }
        return sf::Vector2f(0, 0);
    }

    size_t Sfml::getEntityPointCount(const std::shared_ptr<IEntity> entity)
    {
        for (auto &playerGraphics : _entityGraphics) {
            if (playerGraphics.first.first != entity->getType() ||
            playerGraphics.first.second != entity->getId())
                continue;
            return playerGraphics.second.pointCount;
        }
        return 3;
    }

    void Sfml::resetViewPos(void)
    {
        _view.setSize(GUI_WIDTH, GUI_HEIGHT);
        _view.setRotation(0);
        _view.setCenter(GUI_WIDTH / 2.f, GUI_HEIGHT / 2.f);
        _view.move(-500, -30);
    }
} // namespace Zappy
