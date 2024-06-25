/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** state.cpp
*/

#include "DebugMode.hpp"

namespace Zappy {
    void DebugMode::activate(raylib::Camera &camera) {
        camera.SetPosition(raylib::Vector3(0, 2, -5) * _gridSize);
        camera.SetTarget(raylib::Vector3(0, 1, 7) * _gridSize);
        // Ambient light level (some basic lighting)
        int ambientLoc = GetShaderLocation(_shader, "ambient");
        float ambientLight = 0.8f;
        float array[4] = { ambientLight, ambientLight, ambientLight, 1.0f };
        SetShaderValue(_shader, ambientLoc, array, SHADER_UNIFORM_VEC4);
        _activated = true;
    }

    void DebugMode::desactive(raylib::Camera &camera, const raylib::Vector3 &defaultCamPos,
            const raylib::Vector3 &defaultCamTarget, float defaultAmbientLight) {
        camera.SetPosition(defaultCamPos);
        camera.SetTarget(defaultCamTarget);
        // Ambient light level (some basic lighting)
        int ambientLoc = GetShaderLocation(_shader, "ambient");
        float array[4] = { defaultAmbientLight, defaultAmbientLight, defaultAmbientLight, 1.0f };
        SetShaderValue(_shader, ambientLoc, array, SHADER_UNIFORM_VEC4);
        _activated = false;
    }
}
