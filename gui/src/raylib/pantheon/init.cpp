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
    _steveAnims(raylib::ModelAnimation::Load(_assetsRoot + "models/steve.glb")),
    _arena(raylib::Model(_assetsRoot + "models/pantheon_pedestal.glb")) {

         // Start positions of the camera
        _startPos = raylib::Vector3(-gridSize * 30, _gridSize * 5, -_gridSize * 32);
        _startTarget = raylib::Vector3(-gridSize * 10, -gridSize * 10, gridSize * 37);

        // Index of the current pokemon we're showing
        _currentShowPosition = raylib::Vector3(-_gridSize * 9.4, 0, -gridSize * 6.1);
        _currentShowTarget = raylib::Vector3(_gridSize * 65, _gridSize * 2.7 , -_gridSize * 11.5);


        _arenaPos = raylib::Vector3(_gridSize * 2, 0, _gridSize * 4);

        _stevePos = raylib::Vector3(-_gridSize * 7, -_gridSize * 1.8, _gridSize * 4);

        _endingPosition = raylib::Vector3(-gridSize * 23.7, _gridSize * 1, _gridSize * 5);
        _endingTarget = raylib::Vector3(gridSize * 50.5, -_gridSize * 8, _gridSize * 2);
    }
}
