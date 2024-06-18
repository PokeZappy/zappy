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

        private:
            bool containsPlayer(std::shared_ptr<Player> player);
            void drawItem(size_t x, size_t y, size_t id, size_t quantity);

            raylib::Window _window;
            raylib::Camera _camera;
            std::vector<std::unique_ptr<PlayerRaylib>> _players;

            // floor
            raylib::Texture2D _floorTexture;
            Mesh _floorMesh;
            Material _floorMaterial;

            raylib::Model _tv;

            raylib::Model _itemModel;
            std::vector<raylib::ModelAnimation> _itemAnimations;
            size_t _itemAnimationFrame = 0;
            raylib::Shader _shader;
    };
}
