/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Skybox.hpp
*/

#pragma once

#include "raylib-cpp.hpp"

namespace Zappy {
    class Skybox {
        public:
            Skybox(const std::string &assetsRoot);
            void draw();
        private:
            Model _skybox;
            int _daytimeLoc;
            int _dayrotationLoc;
            int _moveFactorLoc;

            float _daytime = 0.0f;
            float _moveFactor = 0.0f;
    };
}