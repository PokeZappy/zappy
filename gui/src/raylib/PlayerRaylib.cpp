/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.cpp
*/

#include "PlayerRaylib.hpp"

namespace Zappy
{
    PlayerRaylib::PlayerRaylib(const std::shared_ptr<Player> &worldPlayer,
        PokemonInfo &pkInfo, size_t gridSize, raylib::Shader &shader)
        : worldPlayer(worldPlayer), AEntityRaylib(gridSize),
        _model(raylib::Model("assets/models/pokemons/" + pkInfo.id + ".glb")),
        _modelAnimations(raylib::ModelAnimation::Load("assets/models/pokemons/" + infos.id + ".glb"))
    {
        color = raylib::Color::White();
        infos = pkInfo;
        loadShinyTexture();
        _model.materials[1].shader = shader;

        offset = raylib::Vector2(
                Utils::generateRandomFloat(gridSize / 3),
                Utils::generateRandomFloat(gridSize / 3));
        _currentPos = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());
        _textImage = raylib::Image(256, 256, raylib::Color(0, 0, 0, 0));
        _textTexture = raylib::Texture2D(_textImage);
        _textRenderTexture = LoadRenderTexture(256, 256);

        _animationIndexes["idle"] = getAnimationIndex({"ground_idle"});
        _animationIndexes["walk"] = getAnimationIndex({"ground_run", "ground_walk"});
        // TraceLog(LOG_ERROR, "%i", _animationIndexes["walk"]);

        for (int i = 0; i < _modelAnimations.size(); i++) {
            // TraceLog(LOG_ERROR, "%s", std::string(_modelAnimation[i].name).c_str());
        }

        _height += rand() % 20;
    }

    void PlayerRaylib::loadTextureAndModel(void)
    {
        _model = raylib::Model("assets/models/pokemons/" + infos.id + ".glb");
        loadShinyTexture();
        _modelAnimations = raylib::ModelAnimation::Load("assets/models/pokemons/" + infos.id + ".glb");
    }

    void PlayerRaylib::loadShinyTexture(void)
    {
        if (infos.shiny)
        {
            std::string path = "assets/textures/" + infos.id + "_shiny.png";
            Texture2D textureShiny = LoadTexture(path.c_str()); // Load model texture

            _model.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = textureShiny;
        }
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
        if (worldPlayer->isIncanting()) {
            _verticalRotation = sin(GetTime() * 2) * 10;
        } else {
            _verticalRotation = 0;
        }
        // Text
        if (worldPlayer->getLevel() != _level) {
            _level = worldPlayer->getLevel();
            _textImage.ClearBackground(raylib::Color(0, 0, 0, 0));
            _textImage.DrawText(std::to_string(worldPlayer->getId()), 10, 10, 80, raylib::Color::Black());
            _textImage.DrawText(std::string("Level ") + std::to_string(_level), 10, 80, 50, raylib::Color::Black());
            _textTexture.Update(_textImage.data);
        }

        // die
        if (_isDying) {
            move(raylib::Vector3((float)(rand() % 3 - 1) / 20,
                _altitude * 1.04 + 0.01, (float)(rand() % 3 - 1) / 20));
            _scale *= 0.997;
        }

        if (_altitude <= 0) {
            _altitude = 0;
        }
        raylib::Vector2 posGoal(worldPlayer->getX(), worldPlayer->getY());
        raylib::Vector2 deltaMove((posGoal - _currentPos) / 20);

        _currentPos += deltaMove;
        bool isMoving = deltaMove.x != 0 || deltaMove.y != 0;
        if (isMoving) {
            _animFrame++;
        }
        // float meteoriteValue = std::exp((deltaMove.x + deltaMove.y) * 10);
        // if (meteoriteValue > 5)
        //     _verticalRotation = meteoriteValue;
        // _altitude = (deltaMove.x * deltaMove.x + deltaMove.y * deltaMove.y) * 100;
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
            _currentPos.x * _gridSize + offset.x,
            _altitude + std::abs(_verticalRotation * 5),
            _currentPos.y * _gridSize + offset.y};
        if (_animIndex != -1) {
            _model.UpdateAnimation(_modelAnimations[_animIndex], _animFrame);
        }
        // _model.Draw((Vector3) {50, 50, 50},
        //     raylib::Vector3(_verticalRotation, 1, 0), _currentOrientation + (std::abs(_verticalRotation * 80) * worldPlayer->getLevel()),
        //     raylib::Vector3(_scale, _scale, _scale));
        _model.Draw(playerPos,
            raylib::Vector3(_verticalRotation, 1, 0), _currentOrientation + (std::abs(_verticalRotation * 80) * worldPlayer->getLevel()),
            raylib::Vector3(_scale, _scale, _scale));
        playerPos.y += _height + 5;
        _textTexture.DrawBillboard(camera, playerPos, 15);
    }

    int PlayerRaylib::getAnimationIndex(const std::vector<std::string> &names)
    {
        for (size_t i = 0; i < _modelAnimations.size(); i++) {
            std::string animName(_modelAnimations[i].name);
            for (size_t j = 0; j < names.size(); j++) {
                if (animName.find(names[j]) != std::string::npos) {
                    return i;
                }
            }
        }
        return -1;
    }
} // namespace Zappy
