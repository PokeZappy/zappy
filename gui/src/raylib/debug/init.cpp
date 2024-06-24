/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** init.cpp
*/

#include "DebugMode.hpp"

namespace Zappy
{
    DebugMode::DebugMode(const std::string &assetsRoot, raylib::Shader &shader, float gridSize) :
        _assetsRoot(assetsRoot),
        _gridSize(gridSize),
        _model(raylib::Model(_assetsRoot + "models/pokemons/ditto.glb")),
        _animations(raylib::ModelAnimation::Load(_assetsRoot + "models/pokemons/ditto.glb")),
        _shader(shader)
    {
        _scaleModel = _gridSize / 4;

        changeAnimationIndex(0);
        for (const auto &entry : std::filesystem::directory_iterator(_assetsRoot + "models/pokemons/"))
        {
            if (entry.is_regular_file())
            {
                _modelsId.push_back(Utils::remove_extension(entry.path().filename().string()));
            }
        }
        loadModel();
    };
}
