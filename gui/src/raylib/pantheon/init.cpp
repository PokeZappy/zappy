/*
** EPITECH PROJECT, 2023
** gui
** File description:
** init.cpp
*/

#include "Pantheon.hpp"

namespace Zappy {
    Pantheon::Pantheon(std::string assetsRoot, float gridSize, Camera &camera) :
    _assetsRoot(assetsRoot), _gridSize(gridSize), _camera(camera),
    _typesTexture(assetsRoot + TYPES_TEXTURE_PATH),
    _steve(raylib::Model(_assetsRoot + "models/steve.glb")),
    _steveAnims(raylib::ModelAnimation::Load(_assetsRoot + "models/steve.glb")) {
        _theme = raylib::Music(assetsRoot + "menu/SouthProvince.ogg");
        _theme.SetLooping(true);
        _theme.SetVolume(0.08);

         // Start positions of the camera
        _startPos = raylib::Vector3(-1.17, 0.57, -1.14);
        _startTarget = raylib::Vector3(-1.15, 0.56, -1.08);

        // Index of the current pokemon we're showing
        _currentShowPosition = raylib::Vector3(0.15, 0.05, 0);
        _currentShowTarget = raylib::Vector3(0.22, 0.04, 0);

        pokemonSpacing = 0.2;
    }
}
