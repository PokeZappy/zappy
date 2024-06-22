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
            void addPlayer(std::shared_ptr<PlayerRaylib> player) { _selectedPlayers.push_back(player); }
            void clearPlayers() { _selectedPlayers.clear(); }
            void drawBackground();
            void drawInventory(bool player);
            void drawPlayers();

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
