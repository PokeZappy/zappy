/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Raylib.hpp
*/

#pragma once

#include "AGraphicalModule.hpp"
#include "raylib-cpp.hpp"
#include "PlayerRaylib.hpp"
#include "Utils.hpp"
#include <libconfig.h++>
#include "PokemonInfo.hpp"

namespace Zappy {
    class Raylib : public AGraphicalModule {
        #define GUI_WIDTH 1920
        #define GUI_HEIGHT 1080
        public:
            Raylib();
            void render(const World &world) override;
            void update(const World &world) override;
            bool isOpen(void) override;
            void drawTiles(const std::vector<std::vector<Tile>> &tiles) override;
            PokemonInfo getPokemon(std::string team);
            PokemonInfo parsePokemon(libconfig::Setting &pokemon);
            void testEvolution(void);
        private:
            bool containsPlayer(std::shared_ptr<Player> player);
            void drawFood(float x, float y, size_t quantity);
            void drawRock(float x, float y, size_t id, size_t quantity);

            raylib::Window _window;
            raylib::Camera _camera;
            std::vector<std::unique_ptr<PlayerRaylib>> _players;
            std::vector<std::string> listTypes;
            libconfig::Config _configuration;

            // floor
            raylib::Texture2D _floorTexture;
            raylib::Texture2D _hitGridTexture;
            Mesh _floorMesh;
            Material _floorMaterial;
            Material _hitGridMaterial;

            raylib::Model _tv;

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
    };
}
