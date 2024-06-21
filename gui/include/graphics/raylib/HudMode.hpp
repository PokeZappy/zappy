/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** HudMode.hpp
*/

#pragma once

#include "Raylib.hpp"

#define BACKGROUND_HUG_PATH "assets/textures/overlay_message.png"

namespace Zappy {
    class HudMode {
        public: 
            HudMode() : _backgroundHud(BACKGROUND_HUG_PATH) {
            };
            void switchState() { _activated = !_activated; }
            bool activated() { return _activated; }
            void setTile(std::shared_ptr<Tile> tile) { _selectedTile = tile; }
            std::shared_ptr<Tile> getTile() { return _selectedTile; }
            std::vector<std::shared_ptr<PlayerRaylib>> getPlayers() { return _selectedPlayers; }
            void drawBackground() {
                raylib::Rectangle src(0, 0, _backgroundHud.width, _backgroundHud.height);
                raylib::Rectangle dest(0, GUI_HEIGHT - 250, GUI_WIDTH, 200);
                _backgroundHud.Draw(src, dest);
             }
        private:
            bool _activated = false;

            raylib::Texture2D _backgroundHud;
            Rectangle rectangle;

            std::shared_ptr<Tile> _selectedTile = nullptr;
            std::vector<std::shared_ptr<PlayerRaylib>> _selectedPlayers;
    };
}
