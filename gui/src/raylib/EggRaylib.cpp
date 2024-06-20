/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EggRaylib.cpp
*/

#include "EggRaylib.hpp"

namespace Zappy {
    EggRaylib::EggRaylib(const std::shared_ptr<Egg> &egg, raylib::Model &model,
        std::vector<raylib::ModelAnimation> &animations,
        size_t gridSize, raylib::Shader &shader)
        : worldEgg(egg), _model(model), _modelAnimations(animations),
        AEntityRaylib(gridSize)
    {
        _scale = 2.0f;
        color = raylib::Color::White();

        _model.materials[1].shader = shader;

        offset = raylib::Vector2(
                Utils::generateRandomFloat(gridSize / 3),
                Utils::generateRandomFloat(gridSize / 3));
        _currentPos = raylib::Vector2(worldEgg->getX(), worldEgg->getY());
        _textImage = raylib::Image(256, 256, raylib::Color(0, 0, 0, 0));
        _textTexture = raylib::Texture2D(_textImage);
        _textRenderTexture = LoadRenderTexture(256, 256);

        _animationIndexes["idle"] = getAnimationIndex({"ground_idle"});
        _animationIndexes["faint"] = getAnimationIndex({"faint"});
        _animationIndexes["sleep"] = getAnimationIndex({"sleep"});
        _animationIndexes["cry"] = getAnimationIndex({"cry"});
        // TraceLog(LOG_ERROR, "%i", _animationIndexes["walk"]);

        for (int i = 0; i < _modelAnimations.size(); i++) {
            // TraceLog(LOG_ERROR, "%s", std::string(_modelAnimation[i].name).c_str());
        }

        _height += rand() % 20;

        // _textImage.ClearBackground(raylib::Color(0, 0, 0, 0));
        // _textImage.DrawText(std::to_string(worldEgg->getId()), 10, 10, 80, raylib::Color::Black());
        // _textTexture.Update(_textImage.data);
    }

    void EggRaylib::update(void)
    {
        // die, TODO à changer à terme pour l'animation faint de l'oeuf
        if (_isDying) {
            move(raylib::Vector3((float)(rand() % 3 - 1) / 20,
                _altitude * 1.04 + 0.01, (float)(rand() % 3 - 1) / 20));
            _scale *= 0.997;
        }

        if (_altitude <= 0) {
            _altitude = 0;
        }

        _animFrame++;
        // float meteoriteValue = std::exp((deltaMove.x + deltaMove.y) * 10);
        // if (meteoriteValue > 5)
        //     _verticalRotation = meteoriteValue;
        // _altitude = (deltaMove.x * deltaMove.x + deltaMove.y * deltaMove.y) * 100;
        if (_animationIndexes["idle"] != -1)
            _animIndex = _animationIndexes["idle"];
        // if (_hasIdleAnim && _currentPos == posGoal) {
        //     if (_animationIndexes["idle"] != -1) {
        //         _animIndex = _animationIndexes["idle"];
        //     }
        // }
    }

    void EggRaylib::draw(const raylib::Camera camera)
    {
        // draw
        raylib::Vector3 playerPos = raylib::Vector3{
            _currentPos.x * _gridSize + offset.x,
            _altitude,
            _currentPos.y * _gridSize + offset.y};
        if (_animIndex != -1) {
            // TraceLog(LOG_ERROR, "animationIndex = %d avec animFrame = %d", _animIndex, _animFrame);
            _model.UpdateAnimation(_modelAnimations[_animIndex], _animFrame);
        }
        // TraceLog(LOG_ERROR, "metamorph draw");
        _model.Draw(playerPos,
            raylib::Vector3(0, 1, 0), 0,
            raylib::Vector3(_scale, _scale, _scale));
        playerPos.y += _height + 5;
        _textTexture.DrawBillboard(camera, playerPos, 15);
    }

    int EggRaylib::getAnimationIndex(const std::vector<std::string> &names)
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
}
