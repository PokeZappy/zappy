/*
** EPITECH PROJECT, 2023
** gui
** File description:
** init.cpp
*/

#include "Pantheon.hpp"
#include "Raylib.hpp"

namespace Zappy {
    Pantheon::Pantheon(std::string assetsRoot, Raylib &raylib) : _assetsRoot(assetsRoot), _raylib(raylib), _typesTexture(assetsRoot + TYPES_TEXTURE_PATH),
        _steve(raylib::Model(_assetsRoot + "models/steve.glb")),
        _steveAnims(raylib::ModelAnimation::Load(_assetsRoot + "models/steve.glb")) {
        _theme = raylib::Music(assetsRoot + "menu/SouthProvince.ogg");
        _theme.SetLooping(true);
        _theme.SetVolume(0.08);
    }
}