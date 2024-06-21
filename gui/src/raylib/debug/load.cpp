/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** load_model.cpp
*/

#include "DebugMode.hpp"

namespace Zappy {
    void DebugMode::loadModel() {
        _model = raylib::Model("assets/models/pokemons/" + _modelsId[_modelIndex] + ".glb");
        _animations = raylib::ModelAnimation::Load("assets/models/pokemons/" + _modelsId[_modelIndex] + ".glb");
        _oldTexture = _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture;
        changeTexture();
        for (int i = 0; i < _model.materialCount; i++)
            _model.materials[i].shader = _shader;
    }
}
