/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** draw.cpp
*/

#include "Raylib.hpp"
#include "HudMode.hpp"

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
            _selectedPlayer = nullptr;
            white.DrawText("Aucun pokemon à afficher", 644, GUI_HEIGHT - 140, 65);
        } else {
            if (_selectedPlayer == nullptr) {
                _selectedPlayer = _selectedPlayers[0];
            }
            drawPokemons();
            drawInventory(true);
            _attackHudTexture.Draw(_attackSrc, _attackDest);
        }
    }

    void HudMode::drawInventory(bool player) {
        Inventory inventory;
        int x = player ? 900 : 0;
        std::string title = player ? "Pokemon" : std::string("Tile ") + std::to_string(_selectedTile->getY()) + " " + std::to_string(_selectedTile->getX());
        raylib::Color white = raylib::Color::White();
        raylib::Rectangle _inventorySrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
        raylib::Rectangle _inventoryDest(x, GUI_HEIGHT - 200, 265, 200);

        if (player) {
            inventory = _selectedPlayer->worldPlayer->getInventory();
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

    void HudMode::drawPokemons() {
        for (int i = 0; i < 4 && i < _selectedPlayers.size(); i++) {
            drawPokemon(_selectedPlayers[i], GUI_HEIGHT - 171 + (i * 43));
        }
    }

    void HudMode::drawPokemon(std::shared_ptr<PlayerRaylib> pokemon, int y) {
        raylib::Color white = raylib::Color::White();

        if (pokemon == _selectedPlayer) {
            white.DrawText(">", 286, y, 30);
        }
        white.DrawText(std::to_string(pokemon->worldPlayer->getId()), 336, y, 25);
        white.DrawText(pokemon->infos.displayName, 402, y, 25);
        white.DrawText("N." + std::to_string(pokemon->worldPlayer->getLevel()), 582, y, 25);

        drawType(pokemon->worldPlayer->getTeam().getName(), y);

        if (pokemon->worldPlayer->getIncantationState() == Incantation::INCANTING) {
            _encantingTexture.Draw(raylib::Rectangle(0, 0, _encantingTexture.width, _encantingTexture.height), raylib::Rectangle(815, y, 22, 29));
        } else {
            _notEncantingTexture.Draw(raylib::Rectangle(0, 0, _notEncantingTexture.width, _notEncantingTexture.height), raylib::Rectangle(815, y, 22, 29));
        }
    }

    void HudMode::drawType(std::string type, int y) {
        raylib::Color white = raylib::Color::White();
        raylib::Rectangle src;
        raylib::Rectangle dest(701, y, 85, 30);
        if (type == "bug") {
            src = raylib::Rectangle(0, 14, _typesTexture.width, 14);
        } else if (type == "dark") {
            src = raylib::Rectangle(0, 28, _typesTexture.width, 14);
        } else if (type == "dragon") {
            src = raylib::Rectangle(0, 42, _typesTexture.width, 14);
        } else if (type == "electric") {
            src = raylib::Rectangle(0, 56, _typesTexture.width, 14);
        } else if (type == "fairy") {
            src = raylib::Rectangle(0, 70, _typesTexture.width, 14);
        } else if (type == "fight") {
            src = raylib::Rectangle(0, 84, _typesTexture.width, 14);
        } else if (type == "fire") {
            src = raylib::Rectangle(0, 98, _typesTexture.width, 14);
        } else if (type == "fly") {
            src = raylib::Rectangle(0, 112, _typesTexture.width, 14);
        } else if (type == "ghost") {
            src = raylib::Rectangle(0, 126, _typesTexture.width, 14);
        } else if (type == "grass") {
            src = raylib::Rectangle(0, 140, _typesTexture.width, 14);
        } else if (type == "ground") {
            src = raylib::Rectangle(0, 154, _typesTexture.width, 14);
        } else if (type == "ice") {
            src = raylib::Rectangle(0, 168, _typesTexture.width, 14);
        } else if (type == "normal") {
            src = raylib::Rectangle(0, 182, _typesTexture.width, 14);
        } else if (type == "poison") {
            src = raylib::Rectangle(0, 196, _typesTexture.width, 14);
        } else if (type == "psychic") {
            src = raylib::Rectangle(0, 210, _typesTexture.width, 14);
        } else if (type == "rock") {
            src = raylib::Rectangle(0, 224, _typesTexture.width, 14);
        } else if (type == "steel") {
            src = raylib::Rectangle(0, 238, _typesTexture.width, 14);
        } else if (type == "water") {
            src = raylib::Rectangle(0, 252, _typesTexture.width, 14);
        } else {
            white.DrawText(type, 701, y, 25);
        }
        _typesTexture.Draw(src, dest);
    }
}
