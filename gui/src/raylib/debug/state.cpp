/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** state.cpp
*/

#include "DebugMode.hpp"

namespace Zappy {
    void DebugMode::activate(raylib::Camera &camera) {
        camera.SetPosition((Vector3) {0, 60, -250});
        camera.SetTarget((Vector3){0, 0, 0});
        _activated = true;
    }

    void DebugMode::desactive(raylib::Camera &camera) {
        camera.SetPosition((Vector3) {-264, 219, 248});
        camera.SetTarget((Vector3) {-51, 78, 254});
        _activated = false;
    }
}