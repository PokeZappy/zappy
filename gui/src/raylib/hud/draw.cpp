/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** draw.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
     void HudMode::drawBackground() {
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

            void HudMode::drawInventory(bool player) {
                Inventory inventory;
                int x = player ? 900 : 0;
                std::string title = player ? "Pokemon" : "Tile";
                raylib::Color white = raylib::Color::White();
                raylib::Rectangle _inventorySrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
                raylib::Rectangle _inventoryDest(x, GUI_HEIGHT - 200, 265, 200);

                if (player) {
                    inventory = _selectedPlayers[0]->worldPlayer->getInventory();
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

            void HudMode::drawPlayers() {
                raylib::Color white = raylib::Color::White();

            }
}