/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EscapeMenu.hpp
*/

#pragma once

#include "TextureButton.hpp"
#include "StringButton.hpp"
#include "Layout.hpp"
#include <functional>

#define BASEWINDOW_HUD_PATH "textures/hud/base_window.png"
#define INVENTORY_HUD_PATH "textures/hud/inventory.png"
#define ATTACK_HUD_PATH "textures/hud/attack.png"

namespace Zappy {
    class Raylib;

    class EscapeMenu {
    public:
        EscapeMenu(const std::string &assetsRoot, Raylib &core);

        void switchState() { _activated = !_activated; }
        bool activated() { return _activated; }
        void update(Raylib &core);

        void draw(void) {
            if (!_activated)
                return;
            _blackTransp.DrawRectangle(0, 0, Layout::w(), Layout::h());

            int margin = Layout::s(_rightMargin);
            int optionsWidth = Layout::s(_minOptionsWidth);
            int titleSize = Layout::s(60);
            int commandTextSize = Layout::s(20);
            int lineStep = commandTextSize + Layout::s(5);
            int panelY = Layout::top(400);
            int adminCommandY = Layout::top(410);
            int firstCommandY = Layout::top(470);
            int commandX = Layout::left(_rightMargin + 15);

            // options panel hugs the right edge, admin panel the left
            raylib::Color(255, 255, 255, 40).DrawRectangle(raylib::Rectangle(
                Layout::w() - optionsWidth - margin * 2, panelY,
                optionsWidth + margin + margin / 2, Layout::s(500)));
            raylib::Color(255, 255, 255, 40).DrawRectangle(raylib::Rectangle(
                margin, panelY, Layout::s(650), Layout::s(300)));

            raylib::Color::Black().DrawText("Options :",
                Layout::w() - MeasureText("Options :", titleSize) - margin, adminCommandY, titleSize);
            raylib::Color::Black().DrawText("Admin Commands :", Layout::left(_rightMargin + 10), adminCommandY, titleSize);
            raylib::Color::Black().DrawText("Modifier la position:   HACK_POS id x y", commandX, firstCommandY, commandTextSize);
            raylib::Color::Black().DrawText("Modifier la direction:  HACK_DIR id [UP/RIGHT/DOWN/LEFT]", commandX, firstCommandY + lineStep * 1, commandTextSize);
            raylib::Color::Black().DrawText("Modifier le niveau:     HACK_LEVEL id level", commandX, firstCommandY + lineStep * 2, commandTextSize);
            raylib::Color::Black().DrawText("Modifier la vie:        HACK_HEALTH id health", commandX, firstCommandY + lineStep * 3, commandTextSize);
            raylib::Color::Black().DrawText("Tuer un joueur:         KILL id", commandX, firstCommandY + lineStep * 4, commandTextSize);
            raylib::Color::Black().DrawText("Modifier la fréquence:  sst time", commandX, firstCommandY + lineStep * 5, commandTextSize);
            raylib::Color::Black().DrawText("Inventaire d'une case:  HACK_WHOLE_TILE x y food linemate ", commandX, firstCommandY + lineStep * 6, commandTextSize);
            raylib::Color::Black().DrawText("deraumere sibur mendiane phiras thystame", commandX, firstCommandY + lineStep * 7, commandTextSize);
            raylib::Color::Black().DrawText("Ressource d'une case:   HACK_TILE ressource quantity x y", commandX, firstCommandY + lineStep * 8, commandTextSize);
            for (auto &button : _buttons) {
                button->draw();
            }
        }

    private:
        bool _activated = false;
        int _minOptionsWidth;
        int _rightMargin = 25;

        raylib::Texture2D _backgroundHudTexture;
        raylib::Texture2D _inventoryHudTexture;

        // Buttons
        std::vector<std::unique_ptr<IButton>> _buttons;

        // Colors
        raylib::Color _white = raylib::Color::White();
        raylib::Color _blackTransp = raylib::Color(0, 0, 0, 150);
        raylib::Color _green = raylib::Color::Green();

    };
}
