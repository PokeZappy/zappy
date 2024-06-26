/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EscapeMenu.hpp
*/

#pragma once

#include "TextureButton.hpp"
#include "StringButton.hpp"
#include <functional>

#define BASEWINDOW_HUD_PATH "textures/hud/base_window.png"
#define INVENTORY_HUD_PATH "textures/hud/inventory.png"
#define ATTACK_HUD_PATH "textures/hud/attack.png"

namespace Zappy {
    class Raylib;

    class EscapeMenu {
    public:
        EscapeMenu(const std::string &assetsRoot);

        void switchState() { _activated = !_activated; }
        bool activated() { return _activated; }
        void update(Raylib &core);

        void draw(void) {
            if (!_activated)
                return;
            _blackTransp.DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight());

            raylib::Color(255, 255, 255, 40).DrawRectangle(raylib::Rectangle(GUI_WIDTH - _minOptionsWidth - _rightMargin * 2, 400, _minOptionsWidth + _rightMargin + _rightMargin / 2, 500));
            raylib::Color(255, 255, 255, 40).DrawRectangle(raylib::Rectangle(_rightMargin, 400, 650, 300));

            //     commands.push_back("Admin Commands:");
            //     commands.push_back("Modifier la position:   HACK_POS id x y");
            //     commands.push_back("Modifier la direction:  HACK_DIR id [UP/RIGHT/DOWN/LEFT]");
            //     commands.push_back("Modifier le niveau:     HACK_LEVEL id level");
            //     commands.push_back("Donner une ressource:   HACK_GIVE id resource quantity");
            //     commands.push_back("Modifier la vie:        HACK_HEALTH id health");
            //     commands.push_back("Tuer un joueur:         KILL id");
            //     commands.push_back("Modifier la fréquence:  sst time");
            //     commands.push_back("Inventaire d'une case:  HACK_WHOLE_TILE x y food linemate deraumere sibur mendiane phiras thystame");
            //     commands.push_back("Ressource d'une case:   HACK_TILE ressource quantity x y");

            //     commands.push_back("Légende:");
            //     commands.push_back("id: int, 


            raylib::Color::Black().DrawText("Options :", GUI_WIDTH - MeasureText("Options :", 60) - _rightMargin, 410, 60);
            int adminCommandY = 410;
            int firstCommandY = 470;
            int commandTextSize = 20;
            raylib::Color::Black().DrawText("Admin Commands :", _rightMargin + 10, adminCommandY, 60);
            raylib::Color::Black().DrawText("Modifier la position:   HACK_POS id x y", _rightMargin + 15, firstCommandY, commandTextSize);
            raylib::Color::Black().DrawText("Modifier la direction:  HACK_DIR id [UP/RIGHT/DOWN/LEFT]", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 1, commandTextSize);
            raylib::Color::Black().DrawText("Modifier le niveau:     HACK_LEVEL id level", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 2, commandTextSize);
            raylib::Color::Black().DrawText("Modifier la vie:        HACK_HEALTH id health", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 3, commandTextSize);
            raylib::Color::Black().DrawText("Tuer un joueur:         KILL id", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 4, commandTextSize);
            raylib::Color::Black().DrawText("Modifier la fréquence:  sst time", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 5, commandTextSize);
            raylib::Color::Black().DrawText("Inventaire d'une case:  HACK_WHOLE_TILE x y food linemate ", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 6, commandTextSize);
            raylib::Color::Black().DrawText("deraumere sibur mendiane phiras thystame", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 7, commandTextSize);
            raylib::Color::Black().DrawText("Ressource d'une case:   HACK_TILE ressource quantity x y", _rightMargin + 15, firstCommandY + (commandTextSize + 5) * 8, commandTextSize);
            for (auto &button : _buttons) {
                button->draw();
            }
            // raylib::Rectangle _tileSrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
            // raylib::Rectangle _tileDest(100, 100, 265, 200);

            // _inventoryHudTexture.Draw(_tileSrc, _tileDest);
        }
        // void scrollUp(float wheel);
        // void scrollDown(float wheel);
        // void update(void);

    private:
        bool _activated = false;
        int _minOptionsWidth;
        int _rightMargin = 25;

        raylib::Texture2D _backgroundHudTexture;
        raylib::Texture2D _inventoryHudTexture;
        // Rectangle rectangle;

        // size_t _scrollIndex = 0;
        // double _howManyScroll = 0.0f;

        // Buttons
        std::vector<std::unique_ptr<IButton>> _buttons;

        // Colors
        raylib::Color _white = raylib::Color::White();
        raylib::Color _blackTransp = raylib::Color(0, 0, 0, 150);
        raylib::Color _green = raylib::Color::Green();

    };
}
