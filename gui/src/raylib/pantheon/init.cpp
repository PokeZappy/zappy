/*
** EPITECH PROJECT, 2023
** gui
** File description:
** init.cpp
*/

#include "Pantheon.hpp"

namespace Zappy {
    Pantheon::Pantheon(std::string assetsRoot, raylib::Window &window, raylib::Camera &camera, raylib::Shader &shader) : _assetsRoot(assetsRoot), _window(window), _camera(camera), _shader(shader), _typesTexture(assetsRoot + TYPES_TEXTURE_PATH){
        _theme = raylib::Music(assetsRoot + "menu/SouthProvince.ogg");
        _theme.SetLooping(true);
        _theme.SetVolume(0.08);
    }
}