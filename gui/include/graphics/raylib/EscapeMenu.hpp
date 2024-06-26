/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EscapeMenu.hpp
*/

#pragma once

#include "raylib-cpp.hpp"

#define BASEWINDOW_HUD_PATH "textures/hud/base_window.png"
#define INVENTORY_HUD_PATH "textures/hud/inventory.png"

namespace Zappy {
    class EscapeMenu {
    public:
        EscapeMenu(const std::string &assetsRoot) :
            _backgroundHudTexture(assetsRoot + BASEWINDOW_HUD_PATH),
            _inventoryHudTexture(assetsRoot + INVENTORY_HUD_PATH) {}

        void switchState() { _activated = !_activated; }
        bool activated() { return _activated; }

        void draw(void) {
            if (!_activated)
                return;
            _blackTransp.DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight());


            raylib::Rectangle _tileSrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
            raylib::Rectangle _tileDest(100, 100, 265, 200);

            _inventoryHudTexture.Draw(_tileSrc, _tileDest);
        }
        // void scrollUp(float wheel);
        // void scrollDown(float wheel);
        // void update(void);

    private:
        bool _activated = false;

        raylib::Texture2D _backgroundHudTexture;
        raylib::Texture2D _inventoryHudTexture;
        // Rectangle rectangle;

        // size_t _scrollIndex = 0;
        // double _howManyScroll = 0.0f;

        // Colors
        raylib::Color _white = raylib::Color::White();
        raylib::Color _blackTransp = raylib::Color(0, 0, 0, 150);
        raylib::Color _green = raylib::Color::Green();
    };
}
