/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RaylibModel.hpp
*/

#pragma once

namespace Zappy
{
    class RaylibModel {
        public:
            RaylibModel(std::string id, raylib::Shader &shader) : _model("assets/models/pokemons/" + id + ".glb") {
                _animations = raylib::ModelAnimation::Load("assets/models/pokemons/" + id + ".glb");

                _model.materials[1].shader = shader;
                _normalTexture = _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture;
                std::string path = "assets/textures/pokemons/" + id + "_shiny.png";
                _shinyTexture = LoadTexture(path.c_str());
            }
            raylib::Model &getModel() { return (_model); }
            std::vector<raylib::ModelAnimation> &getAnimations() { return (_animations); }
            void setNormalTexture() { _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = _normalTexture; }
            void setShinyTexture() { _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = _shinyTexture; }
            void updateAnimation(int index, int frame) { _model.UpdateAnimation(_animations[index], frame); }
            void draw(raylib::Vector3 position, raylib::Vector3 rotation, float angle, raylib::Vector3 scale) {
                 _model.Draw(position, rotation, angle, scale);
            }
        private:
            raylib::Model _model;
            std::vector<raylib::ModelAnimation> _animations;
            Texture2D _normalTexture;
            Texture2D _shinyTexture;
    };
} // namespace Zappy
