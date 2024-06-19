/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.cpp
*/

#include "PlayerRaylib.hpp"

namespace Zappy
{
    PlayerRaylib::PlayerRaylib(const std::shared_ptr<Player> &worldPlayer, PokemonInfo &pkInfo, size_t gridSize)
        : worldPlayer(worldPlayer), _model("assets/models/pokemons/" + pkInfo.id + ".glb"), _gridSize(gridSize)
    {
        color = raylib::Color::White();
        infos = pkInfo;
        loadTextureAndModel();

        offset = raylib::Vector2(
                Utils::generateRandomFloat(gridSize / 3),
                Utils::generateRandomFloat(gridSize / 3));
        _currentPos = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());
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

    void PlayerRaylib::update(void)
    {
        // die
        if (_isDying) {
            move(raylib::Vector3((float)(rand() % 3 - 1) / 20,
                _height * 1.04 + 0.01, (float)(rand() % 3 - 1) / 20));
            _scale *= 0.997;
        }

        if (_height <= 0) {
            _height = 0;
        }
        _animFrame++;
        raylib::Vector2 posGoal = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());
        _currentPos += (posGoal - _currentPos) / 10;
        _animIndex = 1;
        if (std::abs(_currentPos.x - posGoal.x) < 0.01 && std::abs(_currentPos.y - posGoal.y) < 0.01) {
            _currentPos = posGoal;
        }
        if (_currentPos == posGoal) {
            _animIndex = 0;
        }
    }

    void PlayerRaylib::draw(void)
    {
        float rotationGoal = getRotation();
        _currentOrientation += (rotationGoal - _currentOrientation) / 5;

        // draw
        float scale = 0.5;
        _model.UpdateAnimation(_modelAnimation[_animIndex], _animFrame)
        .Draw(raylib::Vector3{
            _currentPos.x * _gridSize + offset.x, _height,
            _currentPos.y * _gridSize + offset.y},
            raylib::Vector3(0, 1, 0), _currentOrientation,
            raylib::Vector3(_scale, _scale, _scale));
    }

    void PlayerRaylib::move(raylib::Vector3 vector)
    {
        _currentPos.x += vector.x;
        _currentPos.y += vector.z;
        _height = vector.y;
    }
} // namespace Zappy
