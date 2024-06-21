/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** HudMode.hpp
*/

#pragma once

#include "Raylib.hpp"

#define BASEWINDOW_HUD_PATH "assets/textures/hud/base_window.png"
#define INVENTORY_HUD_PATH "assets/textures/hud/inventory.png"
#define ATTACK_HUD_PATH "assets/textures/hud/attack.png"
#define POKEBALL_HUD_PATH "assets/textures/hud/poke_ball.png"
#define SUPERBALL_HUD_PATH "assets/textures/hud/great_ball.png"
#define HYPERBALL_HUD_PATH "assets/textures/hud/ultra_ball.png"
#define HONORBALL_HUD_PATH "assets/textures/hud/premier_ball.png"
#define LUXEBALL_HUD_PATH "assets/textures/hud/luxury_ball.png"
#define MASTERBALL_HUD_PATH "assets/textures/hud/master_ball.png"
#define FOOD_HUD_PATH "assets/textures/hud/pecha_berry.png"

namespace Zappy {
    class HudMode {
        public: 
            HudMode() : _backgroundHudTexture(BASEWINDOW_HUD_PATH), 
                        _inventoryHudTexture(INVENTORY_HUD_PATH),
                        _attackHudTexture(ATTACK_HUD_PATH),
                        _pokeBallTexture(POKEBALL_HUD_PATH),
                        _superBallTexture(SUPERBALL_HUD_PATH),
                        _hyperBallTexture(HYPERBALL_HUD_PATH),
                        _honorBallTexture(HONORBALL_HUD_PATH),
                        _luxeBallTexture(LUXEBALL_HUD_PATH),
                        _masterBallTexture(MASTERBALL_HUD_PATH),
                        _foodTexture(FOOD_HUD_PATH)
                        {
            };
            void switchState() { _activated = !_activated; }
            bool activated() { return _activated; }
            void setTile(std::shared_ptr<Tile> tile) { _selectedTile = tile; }
            std::shared_ptr<Tile> getTile() { return _selectedTile; }
            std::vector<std::shared_ptr<PlayerRaylib>> getPlayers() { return _selectedPlayers; }
            void drawBackground() {
                raylib::Color white = raylib::Color::White();
                raylib::Rectangle _backgroundSrc(0, 0, _backgroundHudTexture.width, _backgroundHudTexture.height);
                raylib::Rectangle _backgroundDest(0, GUI_HEIGHT - 200, GUI_WIDTH, 200);

                raylib::Rectangle _attackSrc(0, 0, _attackHudTexture.width, _attackHudTexture.height);
                raylib::Rectangle _attackDest(GUI_WIDTH - 700, GUI_HEIGHT - 200, 700, 200);

                _backgroundHudTexture.Draw(_backgroundSrc, _backgroundDest);

                if (_selectedTile != nullptr) {
                    drawInventory(false);
                } else {
                    white.DrawText("Séléctionner une tile à afficher", 491, GUI_HEIGHT - 120, 65);
                    return;
                }

                if (_selectedPlayers.empty()) {
                    white.DrawText("Aucun pokemon à afficher", 644, GUI_HEIGHT - 140, 65);
                } else {
                    drawInventory(true);
                    _attackHudTexture.Draw(_attackSrc, _attackDest);
                }
            }

            void drawInventory(bool player) {
                Inventory inventory;
                int x = player ? 900 : 0;
                std::string title = player ? "Pokemon" : "Tile";
                raylib::Color white = raylib::Color::White();
                raylib::Rectangle _inventorySrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
                raylib::Rectangle _inventoryDest(x, GUI_HEIGHT - 200, 265, 200);

                if (player) {
                    inventory = Inventory();
                } else {
                    inventory = _selectedTile->getInventory();
                }
                _inventoryHudTexture.Draw(_inventorySrc, _inventoryDest);
                white.DrawText(title, x + 32, GUI_HEIGHT - 160, 20);


                _pokeBallTexture.Draw(x + 39, GUI_HEIGHT - 129);
                white.DrawText(std::to_string(inventory.getItem(1)), x + 75, GUI_HEIGHT - 129, 20);

                _superBallTexture.Draw(x + 39, GUI_HEIGHT - 98);
                white.DrawText(std::to_string(inventory.getItem(2)), x + 75, GUI_HEIGHT - 98, 20);

                _hyperBallTexture.Draw(x + 39, GUI_HEIGHT - 67);
                white.DrawText(std::to_string(inventory.getItem(3)), x + 75, GUI_HEIGHT - 67, 20);

                _foodTexture.Draw(x + 149, GUI_HEIGHT - 160);
                white.DrawText(std::to_string(inventory.getItem(0)), x + 183, GUI_HEIGHT - 160, 20);

                _honorBallTexture.Draw(x + 149, GUI_HEIGHT - 129);
                white.DrawText(std::to_string(inventory.getItem(4)), x + 183, GUI_HEIGHT - 129, 20);

                _luxeBallTexture.Draw(x + 149, GUI_HEIGHT - 98);
                white.DrawText(std::to_string(inventory.getItem(5)), x + 183, GUI_HEIGHT - 98, 20);

                _masterBallTexture.Draw(x + 149, GUI_HEIGHT - 67);
                white.DrawText(std::to_string(inventory.getItem(6)), x + 183, GUI_HEIGHT - 67, 20);
            }
        private:
            bool _activated = false;

            raylib::Texture2D _backgroundHudTexture;
            raylib::Texture2D _inventoryHudTexture;
            raylib::Texture2D _attackHudTexture;
            raylib::Texture2D _pokeBallTexture;
            raylib::Texture2D _superBallTexture;
            raylib::Texture2D _hyperBallTexture;
            raylib::Texture2D _honorBallTexture;
            raylib::Texture2D _luxeBallTexture;
            raylib::Texture2D _masterBallTexture;
            raylib::Texture2D _foodTexture;
            Rectangle rectangle;

            std::shared_ptr<Tile> _selectedTile = nullptr;
            std::vector<std::shared_ptr<PlayerRaylib>> _selectedPlayers;
    };
}
