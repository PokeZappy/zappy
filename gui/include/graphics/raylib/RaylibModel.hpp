/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RaylibModel.hpp
*/

#pragma once

#include <iostream>
#include "raylib-cpp.hpp"

namespace Zappy
{
    // raylib loads glTF materials at index 1 and up, keeping a default material at
    // index 0. A model that failed to load only has that default one, so indexing 1
    // blindly writes past the end of the array.
    inline int modelMaterialIndex(const ::Model &model)
    {
        return (model.materialCount > 1) ? 1 : 0;
    }

    class RaylibModel {
        public:
            RaylibModel(const std::string &assetsRoot, std::string id,
                raylib::Shader &shader, int animIndex) :
                _model(assetsRoot + "models/pokemons/" + id + ".glb"),
                _animIndex(animIndex)
            {
                _materialIndex = modelMaterialIndex(_model);
                if (_model.materialCount <= 1) {
                    std::cerr << "RaylibModel: '" << id
                        << "' has no loaded material, the model is probably missing"
                        << std::endl;
                }
                _model.materials[_materialIndex].shader = shader;
            }
            const raylib::Model &getModel() const { return (_model); }
            Texture2D getTexture() { return _model.materials[_materialIndex].maps[MATERIAL_MAP_DIFFUSE].texture; }
            void setTexture(Texture2D &texture) {
                _model.materials[_materialIndex].maps[MATERIAL_MAP_DIFFUSE].texture = texture; }
            void updateAnimation(std::vector<raylib::ModelAnimation> &animations) { 
                if (_animIndex != -1)
                    _model.UpdateAnimation(animations[_animIndex], _frame); 
                _frame++; }
            void draw(raylib::Vector3 position, raylib::Vector3 rotation, float angle, raylib::Vector3 scale, raylib::Color tint = raylib::Color::White()) {
                 _model.Draw(position, rotation, angle, scale, tint);
            }
        private:
            raylib::Model _model;
            int _frame = 0;
            int _animIndex;
            int _materialIndex = 0;
    };
} // namespace Zappy
