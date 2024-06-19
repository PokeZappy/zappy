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
        _textImage = raylib::Image(256, 256, raylib::Color(0, 0, 0, 0));
        _textTexture = raylib::Texture2D(_textImage);

        _animationIndexes["idle"] = getAnimationIndex({"ground_idle"});
        _animationIndexes["walk"] = getAnimationIndex({"ground_run", "ground_walk"});
    }

    int PlayerRaylib::getAnimationIndex(const std::vector<std::string> &names)
    {
        for (size_t i = 0; i < _modelAnimation.size(); i++) {
            // std::cout << "name: " << _modelAnimation[i].name << std::endl;
            for (size_t j = 0; j < names.size(); j++) {
                if (_modelAnimation[i].name == names[j]) {
                    return i;
                }
            }
        }
        return -1;
    }

    void PlayerRaylib::loadTextureAndModel(void)
    {
        _model = raylib::Model("assets/models/pokemons/" + infos.id + ".glb");
        if (infos.shiny)
        {
            std::string path = "assets/textures/" + infos.id + "_shiny.png";
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
        // Text
        _textImage.ClearBackground(raylib::Color(0, 0, 0, 0));
        _textImage.DrawText(std::to_string(worldPlayer->getId()), 10, 10, 80, raylib::Color::Black());
        _textImage.DrawText(std::string("Level ") + std::to_string(worldPlayer->getLevel()), 10, 80, 50, raylib::Color::Black());
        _textTexture.Update(_textImage.data);

        // die
        if (_isDying) {
            move(raylib::Vector3((float)(rand() % 3 - 1) / 20,
                _altitude * 1.04 + 0.01, (float)(rand() % 3 - 1) / 20));
            // _altitude *= 1.04 + 0.01
            _scale *= 0.997;
        }

        if (_altitude <= 0) {
            _altitude = 0;
        }
        _animFrame++;
        raylib::Vector2 posGoal = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());
        _currentPos += (posGoal - _currentPos) / 10;
        if (_animationIndexes["walk"] != -1)
            _animIndex = _animationIndexes["walk"];
        if (std::abs(_currentPos.x - posGoal.x) < 0.01 && std::abs(_currentPos.y - posGoal.y) < 0.01) {
            _currentPos = posGoal;
        }
        if (_hasIdleAnim && _currentPos == posGoal) {
            if (_animationIndexes["idle"] != -1) {
                _animIndex = _animationIndexes["idle"];
            }
        }
    }

    void PlayerRaylib::draw(const raylib::Camera camera)
    {
        float rotationGoal = getRotation();
        _currentOrientation += (rotationGoal - _currentOrientation) / 5;

        // draw
        float scale = 0.5;
        raylib::Vector3 playerPos = raylib::Vector3{
            _currentPos.x * _gridSize + offset.x, _altitude,
            _currentPos.y * _gridSize + offset.y};
        if (_animIndex != -1) {
            _model.UpdateAnimation(_modelAnimation[_animIndex], _animFrame);
        }
        _model.Draw(playerPos,
            raylib::Vector3(0, 1, 0), _currentOrientation,
            raylib::Vector3(_scale, _scale, _scale));
        playerPos.y += _height + 5;
        _textTexture.DrawBillboard(camera, playerPos, 15);
    }

    void PlayerRaylib::move(raylib::Vector3 vector)
    {
        _currentPos.x += vector.x;
        _currentPos.y += vector.z;
        _altitude = vector.y;
    }
} // namespace Zappy
