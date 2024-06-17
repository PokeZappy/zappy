/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Raylib.hpp
*/

#pragma once

#include "AGraphicalModule.hpp"
#include "raylib-cpp.hpp"

namespace Zappy {
    class Raylib : public AGraphicalModule {
        #define GUI_WIDTH 1920
        #define GUI_HEIGHT 1080
        public:
            Raylib();
            void render(const Zappy::World &world) override;
            void update() override;
            bool isOpen() override;
            void drawTiles(const std::vector<std::vector<Tile>> &tiles) override;
            void drawEntity(const std::shared_ptr<IEntity> entity) override;
        private:
            raylib::Window _window;
            raylib::Camera _camera;
    };
}