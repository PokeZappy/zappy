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
            void drawEntity(const std::shared_ptr<IEntity> entity) override;

        private:
            bool containsPlayer(std::shared_ptr<Player> player);


            raylib::Window _window;
            raylib::Camera _camera;
            std::vector<PlayerRaylib> _players;

            // floor
            void createMeshWithTexture(void);
            raylib::Texture2D _floorTexture;
            Mesh _floorMesh;
            Material _floorMaterial;

            raylib::Model _tv;
    };
}
