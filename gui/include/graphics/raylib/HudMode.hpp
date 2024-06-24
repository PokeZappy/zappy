/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** HudMode.hpp
*/

#pragma once

#include "raylib-cpp.hpp"
#include <memory>
#include "Tile.hpp"
#include "PlayerRaylib.hpp"
#include "ClientSocket.hpp"

#define BASEWINDOW_HUD_PATH "textures/hud/base_window.png"
#define INVENTORY_HUD_PATH "textures/hud/inventory.png"
#define ATTACK_HUD_PATH "textures/hud/attack.png"
#define POKEBALL_HUD_PATH "textures/hud/poke_ball.png"
#define SUPERBALL_HUD_PATH "textures/hud/great_ball.png"
#define HYPERBALL_HUD_PATH "textures/hud/ultra_ball.png"
#define HONORBALL_HUD_PATH "textures/hud/premier_ball.png"
#define LUXEBALL_HUD_PATH "textures/hud/luxury_ball.png"
#define MASTERBALL_HUD_PATH "textures/hud/master_ball.png"
#define FOOD_HUD_PATH "textures/hud/pecha_berry.png"
#define TYPES_HUD_PATH "textures/hud/types.png"
#define TYPESFR_HUD_PATH "textures/hud/types_fr.png"
#define NOT_ENCANTING_HUD_PATH "textures/hud/evolution_icon_disabled.png"
#define ENCANTING_HUD_PATH "textures/hud/evolution_icon_enabled.png"

namespace Zappy {
    class HudMode {
    public:
        HudMode(const std::string &assetsRoot, double gridSize) :
            _backgroundHudTexture(assetsRoot + BASEWINDOW_HUD_PATH),
            _inventoryHudTexture(assetsRoot + INVENTORY_HUD_PATH),
            _attackHudTexture(assetsRoot + ATTACK_HUD_PATH),
            _pokeBallTexture(assetsRoot + POKEBALL_HUD_PATH),
            _superBallTexture(assetsRoot + SUPERBALL_HUD_PATH),
            _hyperBallTexture(assetsRoot + HYPERBALL_HUD_PATH),
            _honorBallTexture(assetsRoot + HONORBALL_HUD_PATH),
            _luxeBallTexture(assetsRoot + LUXEBALL_HUD_PATH),
            _masterBallTexture(assetsRoot + MASTERBALL_HUD_PATH),
            _foodTexture(assetsRoot + FOOD_HUD_PATH),
            _typesTexture(assetsRoot + TYPES_HUD_PATH),
            _notEncantingTexture(assetsRoot + NOT_ENCANTING_HUD_PATH),
            _encantingTexture(assetsRoot + ENCANTING_HUD_PATH),
            _gridSize(gridSize) {}
        void switchState() { 
            _activated = !_activated;
            if (_targetedPlayer != nullptr)
                _targetedPlayer = nullptr;
            }
        bool activated() { return _activated; }
        void setTile(std::shared_ptr<Tile> tile) { _selectedTile = tile; }
        std::shared_ptr<Tile> getTile() { return _selectedTile; }
        std::vector<std::shared_ptr<PlayerRaylib>> getPlayers() { return _selectedPlayers; }
        void addPlayer(std::shared_ptr<PlayerRaylib> player) { _selectedPlayers.push_back(player); }
        void clearPlayers() { _selectedPlayers.clear(); }
        void drawBackground();
        void drawInventory(bool player);
        void drawPlayers();
        void drawAttacks();
        void verifyPlayerPosition();
        void drawPokemons();
        void drawPokemon(std::shared_ptr<PlayerRaylib> pokemon, int y);
        void scrollUp(float wheel);
        void scrollDown(float wheel);
        void drawType(std::string type, int y);
        void drawChat();
        void setFirstPokemonTarget();
        void followTarget(raylib::Camera &camera);
        void update(raylib::Camera &camera, ClientSocket &socket);
        void updateChat();
        void setSelectedPlayerToTarget();
        bool isChatEnabled() { return _chat; }

    private:
        bool _activated = false;
        bool _chat = false;

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
        raylib::Texture2D _typesTexture;
        raylib::Texture2D _notEncantingTexture;
        raylib::Texture2D _encantingTexture;
        Rectangle rectangle;

        std::shared_ptr<Tile> _selectedTile = nullptr;
        std::vector<std::shared_ptr<PlayerRaylib>> _selectedPlayers;
        std::shared_ptr<PlayerRaylib> _selectedPlayer;
        std::shared_ptr<PlayerRaylib> _targetedPlayer = nullptr;
        size_t _scrollIndex = 0;
        double _howManyScroll = 0.0f;
        double _gridSize;


        std::string _inputString = "";
    };
}
