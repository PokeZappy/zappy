/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** init.cpp
*/

#include "DebugMode.hpp"

namespace Zappy
{
    DebugMode::DebugMode(raylib::Shader &shader) :
        _model(raylib::Model("assets/models/pokemons/ditto.glb")),
        _animations(raylib::ModelAnimation::Load("assets/models/pokemons/ditto.glb")),
        _shader(shader)
    {
        changeAnimation(0);
        for (const auto &entry : std::filesystem::directory_iterator("assets/models/pokemons/"))
        {
            if (entry.is_regular_file())
            {
                _modelsId.push_back(Utils::remove_extension(entry.path().filename().string()));
            }
        }
        loadModel();
    };
}
