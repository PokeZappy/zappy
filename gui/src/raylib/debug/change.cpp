/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** change.cpp
*/

#include "DebugMode.hpp"

namespace Zappy
{
    void DebugMode::changeModel(std::string idModel)
    {
        auto it = std::find(_modelsId.begin(), _modelsId.end(), idModel);
        if (it != _modelsId.end())
        {
            _modelIndex = std::distance(_modelsId.begin(), it);
            loadModel();
        }
    }

    void DebugMode::changeTexture()
    {
        if (!_shiny) {
            _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = _oldTexture;
            return;
        }
        std::string path = _assetsRoot + "textures/pokemons/" + _modelsId[_modelIndex] + "_shiny.png";
        Texture2D textureShiny = LoadTexture(path.c_str()); // Load model texture

        _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = textureShiny;
    }

    void DebugMode::nextModel()
    {
        _modelIndex++;
        if (_modelIndex >= _modelsId.size())
            _modelIndex = 0;
        changeAnimation(0);
        loadModel();
    }

    void DebugMode::lastModel()
    {
        _modelIndex--;
        if (_modelIndex < 0)
            _modelIndex = _modelsId.size() - 1;
        changeAnimation(0);
        loadModel();
    }

    void DebugMode::changeAnimation(int index) {
        if (index < _animations.size())
            _animIndex = index;
    };

    void DebugMode::changeAnimation(bool increments) {
        if (increments) {
            _animIndex++;
            if (_animIndex >= _animations.size()) 
                _animIndex = 0;
        } else {
            _animIndex--;
            if (_animIndex < 0) 
                _animIndex = _animations.size() - 1;
        }
    };
}
