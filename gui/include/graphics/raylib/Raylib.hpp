/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Raylib.hpp
*/

#pragma once

#include "AGraphicalModule.hpp"
#include "PlayerRaylib.hpp"
#include "EggRaylib.hpp"
#include "Utils.hpp"
#include <libconfig.h++>
#include "DebugMode.hpp"
#include "HudMode.hpp"
#include "EscapeMenu.hpp"
#include "RaylibModel.hpp"
#include "RaylibModels.hpp"

#include "raylib-cpp.hpp"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define POKEBALL_MODEL_PATH "models/poke_ball.glb"
#define FOOD_MODEL_PATH "models/pecha_berry.glb"
#define GAMEBOY_MODEL_PATH "models/dsi1.glb"
#define EGG_MODEL_PATH "models/pokemons/ditto.glb"
#define SUN_MODEL_PATH "models/pokemons/solrock.glb"
#define MOON_MODEL_PATH "models/pokemons/lunatone.glb"
#define ARENA_MODEL_PATH "models/arena.glb"

// #define TILE_TEXTURE_PATH "textures/pokemon_tile.png"
#define TILE_TEXTURE_PATH "textures/ice_tile.png"

#define MAIN_THEME_PATH "menu/SouthProvince.ogg"
#include "ClientSocket.hpp"

namespace Zappy {
    class EscapeMenu;

    namespace Menu {
        enum State {
            STARTING,
            MENU,
            ENDING,
            NONE
        };
    }

    #define SUN_COLOR CLITERAL(Color){252, 255, 181, 255}
    #define MOON_COLOR CLITERAL(Color){81, 81, 176, 255}
    #define ITEM_COLORS {WHITE, CLITERAL(Color){231, 112, 255, 255}, CLITERAL(Color){246, 255, 0, 255}, CLITERAL(Color){255, 137, 0, 255}}
    class Raylib : public AGraphicalModule {
        public:
            Raylib(const std::string &assetsRoot, ClientSocket &socket);
            void render(const World &world) override;
            void renderDebug(void);
            void handleKeys(void);
            void update(const World &world) override;
            void updateMenu();
            void drawMenu();
            void updatePlayers(const World &world);
            void updateEggs(const World &world);

            bool isOpen(void) override;
            void drawTiles(const std::vector<std::vector<Tile>> &tiles) override;
            void drawHud(const World &world);
            PokemonInfo getPokemon(std::string team);
            PokemonInfo parsePokemon(libconfig::Setting &pokemon);
            void testEvolution(void);

            // Getters
            raylib::Window &getWindow() { return (_window); }
            std::shared_ptr<DebugMode> getDebug() { return (debugMode);}
            std::shared_ptr<EscapeMenu> getMenu() { return (_escapeMenu); }
            raylib::Camera &getCamera() { return (_camera); }
        private:
            // Utils
            bool containsPlayer(std::shared_ptr<Player> player);
            bool containsEgg(std::shared_ptr<Egg> egg);
            raylib::Color getTeamColor(const std::string &teamName);
            raylib::Color getTeamColor(const Team &team);
            raylib::Vector3 getSunPosition(double elapsedTime, double cycle_duration_sec);
            // Draw
            void drawFood(float x, float y, size_t quantity);
            void drawRock(float x, float y, size_t id, size_t quantity);

            const std::string &_assetsRoot;
            raylib::Window _window;
            raylib::Camera _camera;
            CameraMode _cameraViewMode = CAMERA_FIRST_PERSON;
            raylib::Vector3 _defaultCameraPosition;
            raylib::Vector3 _defaultCameraTarget;
            std::vector<std::shared_ptr<PlayerRaylib>> _players;
            bool _showPlayers = true;
            std::vector<std::unique_ptr<EggRaylib>> _eggs;
            raylib::Model _eggModel;
            std::vector<raylib::ModelAnimation> _eggModelAnimations;
            size_t _eggAnimFrame = 0;
            std::vector<std::string> _listTypes;
            std::vector<raylib::Color> _listTypesColors;
            std::vector<std::string> _listTypesCustom;
            std::vector<raylib::Color> _listTypesColorsCustom;

            libconfig::Config _configuration;
            std::shared_ptr<DebugMode> debugMode;

            // floor
            raylib::Texture2D _floorTexture;
            raylib::Texture2D _hitGridTexture;
            Mesh _floorMesh;
            Material _floorMaterial;
            Material _hitGridMaterial;

            // -- Models --
            std::unordered_map<std::string, std::shared_ptr<RaylibModels>> _models;

            // Sun & moon
            raylib::Model _sun;
            raylib::Model _moon;

            // Arena
            raylib::Model _arena;
            float _arenaScale = 1.0f;
            float _arenaAltitudeScale = 0.0f;
            float (*getArenaOffset)(size_t tileCount, float gridSize);

            // Rocks (pokeballs)
            raylib::Model _rockModel;
            std::vector<raylib::Texture2D> _rockTextures;
            std::vector<raylib::ModelAnimation> _rockAnimations;
            size_t _rockAnimationIndex = 4;
            size_t _rockAnimationFrame = 0;

            // Food
            raylib::Model _foodModel;

            float _defaultAmbientLight = 0.3f;
            raylib::Shader _shader;
            raylib::Shader _discardTranspShader;
            Light _lights[MAX_LIGHTS];

            // HUD
            std::unique_ptr<HudMode> _hudMode;

            // Escape menu
            std::shared_ptr<EscapeMenu> _escapeMenu;

            // Sounds and Themes
            raylib::Music _mainTheme;

            raylib::Color _itemColors[4] = ITEM_COLORS;

            // Menu
            std::unique_ptr<raylib::Gif> _menuIntroGif;
            std::unique_ptr<raylib::Gif> _menuGif;
            Menu::State _menuState = Menu::STARTING;
            std::chrono::time_point<std::chrono::steady_clock> _menuClock;
            raylib::Vector3 _startPos;
            raylib::Vector3 _endPos;
            raylib::Vector3 _startTarget;
            raylib::Vector3 _endTarget;
            double _startTime = 2.f;
            double _durationEnding = 1.5f;
            bool _forceStartAnimation = false;

            raylib::Gif _broadcastGif;
            raylib::Gif _successGif;
            raylib::Gif _failureGif;
            raylib::Gif _followGif;
            raylib::Gif _pushGif;

            // Server socket
            ClientSocket &_socket;
    };
}
