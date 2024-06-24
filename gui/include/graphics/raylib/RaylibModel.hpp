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
    class RaylibModel {
        public:
            RaylibModel(const std::string &assetsRoot, std::string id,
                raylib::Shader &shader, int animIndex) :
                _model(assetsRoot + "models/pokemons/" + id + ".glb"),
                _animIndex(animIndex)
            {

                _model.materials[1].shader = shader;
            }
            const raylib::Model &getModel() const { return (_model); }
            Texture2D getTexture() { return _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture; }
            void setTexture(Texture2D &texture) { 
                _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = texture; }
            void updateAnimation(std::vector<raylib::ModelAnimation> &animations) { 
                if (_animIndex != -1)
                    _model.UpdateAnimation(animations[_animIndex], _frame); 
                _frame++; }
            void draw(raylib::Vector3 position, raylib::Vector3 rotation, float angle, raylib::Vector3 scale) {
                 _model.Draw(position, rotation, angle, scale);
            }
        private:
            raylib::Model _model;
            int _frame = 0;
            int _animIndex;
    };
} // namespace Zappy
