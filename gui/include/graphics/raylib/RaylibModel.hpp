/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RaylibModel.hpp
*/

#pragma once

#include <iostream>

namespace Zappy
{
    class RaylibModel {
        public:
            RaylibModel(std::string id, raylib::Shader &shader, raylib::ModelAnimation &animation) : _model("assets/models/pokemons/" + id + ".glb"),
                _animation(animation) 
                {

                _model.materials[1].shader = shader;
            }
            const raylib::Model &getModel() const { return (_model); }
            raylib::ModelAnimation &getAnimation() { return (_animation); }
            Texture2D getTexture() { return _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture; }
            void setNormalTexture(Texture2D &texture) { _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = texture; }
            void setShinyTexture(Texture2D &texture) { _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = texture; }
            void updateAnimation() { _model.UpdateAnimation(_animation, _frame); _frame++; }
            void draw(raylib::Vector3 position, raylib::Vector3 rotation, float angle, raylib::Vector3 scale) {
                 _model.Draw(position, rotation, angle, scale);
            }
        private:
            raylib::ModelAnimation &_animation;
            raylib::Model _model;
            int _frame = 0;
    };
} // namespace Zappy
