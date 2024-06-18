/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.cpp
*/

#include "PlayerRaylib.hpp"

namespace Zappy
{
    PlayerRaylib::PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo)
        : worldPlayer(worldPlayer), _model("assets/models/pokemons/" + pkInfo.id + ".glb")
    {
        color = raylib::Color::White();
        infos = pkInfo;
        loadTextureAndModel();

        offset = raylib::Vector2(
            static_cast<float>(rand() % (GRID_SIZE / 4) - (GRID_SIZE / 2)),
            static_cast<float>(rand() % (GRID_SIZE / 4) - (GRID_SIZE / 2)));
        offset = raylib::Vector2(0, 0);
    }

    void PlayerRaylib::loadTextureAndModel(void)
    {
        _model = raylib::Model("assets/models/pokemons/" + infos.id + ".glb");
        if (infos.shiny)
        {
            std::string path = "assets/textures/" + infos.id + "_shiny.png";
            std::cout << "              chemin de fou :" << path << std::endl;
            Texture2D textureShiny = LoadTexture(path.c_str()); // Load model texture

            // raylib::Texture2D textureShiny = raylib::Texture2D::Load("assets/textures/" + pkInfo.id + "_shiny.png");

            _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = textureShiny;
        }
        _modelAnimation = raylib::ModelAnimation::Load("assets/models/pokemons/" + infos.id + ".glb");
    }

    float PlayerRaylib::getRotation(void) const
    {
        switch (worldPlayer->getOrientation())
        {
        case Orientation::NORTH:
            return 180;
        case Orientation::EAST:
            return 270;
        case Orientation::SOUTH:
            return 0;
        case Orientation::WEST:
            return 90;
        }
        return 0;
    }

    void PlayerRaylib::draw(void)
    {
        // update
        _animFrame++;
        raylib::Vector2 pos = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());
        _lastPos += (pos - _lastPos) / 10;
        _animIndex = 1;
        if (std::abs(_lastPos.x - pos.x) < 0.01 && std::abs(_lastPos.y - pos.y) < 0.01)
        {
            _lastPos = pos;
            // _animFrame = 0;
        }
        if (_lastPos == pos)
        {
            _animIndex = 0;
            // _animFrame = 0;
        }

        // draw
        _model.UpdateAnimation(_modelAnimation[_animIndex], _animFrame).Draw(raylib::Vector3{_lastPos.x * GRID_SIZE + offset.x, 0, _lastPos.y * GRID_SIZE + offset.y}, raylib::Vector3(0, 1, 0), getRotation());
    }
} // namespace Zappy
