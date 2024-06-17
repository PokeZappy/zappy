/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.hpp
*/

#pragma once

#include "raylib-cpp.hpp"
#include "Utils.hpp"
#include "Player.hpp"

namespace Zappy {
    class PlayerRaylib {
    public:
        PlayerRaylib() = default;
        PlayerRaylib(const std::shared_ptr<Player> &worldPlayer)
        : worldPlayer(worldPlayer), model("assets/models/pokemons/torterra.glb") {
            color = raylib::Color::White();
            // std::string modelPath = "/Users/antoine/Downloads/torterra.glb";
            // try {
                // model = raylib::Model("assets/models/pokemons/torterra.glb");
            // }
            // catch(const raylib::RaylibException& e)
            // {
                // std::cerr << "could not load model" << std::endl;
            // }

            // offset =  raylib::Vector2(static_cast<float>(rand() % 10 - 5),
            //     static_cast<float>(rand() % 10 - 5));
            offset = raylib::Vector2(0, 0);
        }

        void draw(void) const
        {
            // model.UpdateAnimation(0, 0);
            model.Draw(raylib::Vector3{
                worldPlayer->getX() * GRID_SIZE + offset.x, 0,
                worldPlayer->getY() * GRID_SIZE + offset.y},
                raylib::Vector3(0, 1, 0), getRotation());
        }

        raylib::Color color;
        raylib::Vector2 offset;
        const std::shared_ptr<Player> worldPlayer;
    private:
        float getRotation(void) const {
            switch (worldPlayer->getOrientation()) {
                case Orientation::NORTH:
                    return 180;
                case Orientation::EAST:
                    return 270;
                case Orientation::SOUTH:
                    return 0;
                case Orientation::WEST:
                    return 90;
            }
            return 0;
        }
        raylib::Model model;
    };
} // namespace Zappy
