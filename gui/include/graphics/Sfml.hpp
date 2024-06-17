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
#include "sfml/PlayerGraphics.hpp"
#include "AGraphicalModule.hpp"

namespace Zappy {
    typedef struct mouse_pos_s {
        sf::Vector2i window;
        sf::Vector2f view;
        sf::Vector2i grid;
    } mouse_pos_t;

    class Sfml : public AGraphicalModule {
    #define GUI_WIDTH 1920
    #define GUI_HEIGHT 1080
    public:
        Sfml();
        void update(void) override;
        void render(const World &world) override;
        bool isOpen(void) { return (_window.isOpen()); }

        void updateMouse(void);
        void handleEvent(void);

        void drawTiles(const std::vector<std::vector<Tile>> &tiles) override;
        void drawEntity(const std::shared_ptr<IEntity> entity) override;
        void drawShell(const std::vector<ShellCommand> &shellCommands);
    private:
        void resetViewPos(void);

        // Colors
        sf::Color getTeamColor(TeamType teamType);
        sf::Color getTextColor(const ShellCommand &command);
        sf::Color getEntityColor(const std::shared_ptr<IEntity> player);
        sf::Vector2f getEntityOffset(const std::shared_ptr<IEntity> player);
        size_t getEntityPointCount(const std::shared_ptr<IEntity> entity);
        sf::Color getItemColor(Item itemType);
        sf::Color getRandomColor(void) {
            return sf::Color(50 + rand() % 205, 50 + rand() % 205, 50 + rand() % 205);
        }


        sf::RenderWindow _window;
        sf::View _view;
        double _viewSpeed = 15.0f;
        sf::Font _font;
        mouse_pos_t _mousePositions;

        // Tiles
        int _mapX = -1;
        int _mapY = -1;
        double _tileWidth = -1.f;
        double _tileHeight = -1.f;
        sf::RectangleShape _tileRect;
        sf::RectangleShape _tileSelector;

        // Resources
        sf::Text _resourcesText;

        // Player
        sf::CircleShape _entityTriangle;
        sf::Text _playerLevelText;
        std::map<std::pair<EntityType, size_t>, PlayerGraphics> _entityGraphics;

        // Shell
        sf::Text _shellText;
        sf::RectangleShape _shellTextTeamColor;
    };

} // namespace Zappy
