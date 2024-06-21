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

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#define POKEBALL_MODEL_PATH "assets/models/poke_ball.glb"
#define FOOD_MODEL_PATH "assets/models/pecha_berry.glb"
#define GAMEBOY_MODEL_PATH "assets/models/nintendo_game_boy.glb"
#define EGG_MODEL_PATH "assets/models/pokemons/ditto.glb"
#define SUN_MODEL_PATH "assets/models/sun.glb"
#define MOON_MODEL_PATH "assets/models/pokemons/dusclops.glb"
#define ARENA_MODEL_PATH "assets/local/arena.glb"

namespace Zappy {
    #define SUN_COLOR CLITERAL(Color){252, 255, 181, 255}
    #define MOON_COLOR CLITERAL(Color){81, 81, 176, 255}
    class Raylib : public AGraphicalModule {
        #define GUI_WIDTH 1920
        #define GUI_HEIGHT 1080
        public:
            Raylib();
            void render(const World &world) override;
            void renderDebug(const World &world);
            void update(const World &world) override;
            void updatePlayers(const World &world);
            void updateEggs(const World &world);

            bool isOpen(void) override;
            void drawTiles(const std::vector<std::vector<Tile>> &tiles) override;
            PokemonInfo getPokemon(std::string team);
            PokemonInfo parsePokemon(libconfig::Setting &pokemon);
            void testEvolution(void);
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

            raylib::Window _window;
            raylib::Camera _camera;
            std::vector<std::unique_ptr<PlayerRaylib>> _players;
            std::vector<std::unique_ptr<EggRaylib>> _eggs;
            raylib::Model _eggModel;
            std::vector<raylib::ModelAnimation> _eggModelAnimations;
            size_t _eggAnimFrame = 0;
            std::vector<std::string> _listTypes;
            std::vector<raylib::Color> _listTypesColors;

            libconfig::Config _configuration;
            std::unique_ptr<DebugMode> debugMode;

            // floor
            raylib::Texture2D _floorTexture;
            raylib::Texture2D _hitGridTexture;
            Mesh _floorMesh;
            Material _floorMaterial;
            Material _hitGridMaterial;

            // -- Models --

            // Sun & moon
            raylib::Model _sun;
            raylib::Model _moon;

            // Gameboy & Arena
            raylib::Model _tv;
            raylib::Model _arena;
            float _arenaScale = 1.0f;
            float _arenaAltitudeScale = 0.0f;
            float (*getArenaOffset)(size_t tileCount, size_t gridSize);

            // Rocks (pokeballs)
            raylib::Model _rockModel;
            std::vector<Texture2D> _rockTextures;
            std::vector<raylib::ModelAnimation> _rockAnimations;
            size_t _rockAnimationFrame = 0;

            // Food
            raylib::Model _foodModel;

            // Text
            Texture2D _textTexture;

            raylib::Shader _shader;
            Light _lights[MAX_LIGHTS];

            bool _selectionMode = true;
    };
}
