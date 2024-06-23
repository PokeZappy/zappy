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
        float gridSize, raylib::Shader &shader, raylib::Color tint)
        : worldEgg(egg), _model(model), _modelAnimations(animations), _tint(tint),
        AEntityRaylib(gridSize)
    {
        _scale = _gridSize * 0.06;

        _model.materials[1].shader = shader;

        offset = raylib::Vector2(
                Utils::generateRandomFloat(gridSize / 3),
                Utils::generateRandomFloat(gridSize / 3));
        _currentPos = raylib::Vector2(worldEgg->getX(), worldEgg->getY());
        // _textImage = raylib::Image(256, 256, raylib::Color(0, 0, 0, 0));
        // _textTexture = raylib::Texture2D(_textImage);
        // _textRenderTexture = LoadRenderTexture(256, 256);

        _animationIndexes["idle"] = getAnimationIndex({"ground_idle"});
        _animationIndexes["faint"] = getAnimationIndex({"faint"});
        _animationIndexes["sleep"] = getAnimationIndex({"sleep"});
        _animationIndexes["cry"] = getAnimationIndex({"cry"});
        // TraceLog(LOG_ERROR, "%i", _animationIndexes["walk"]);

        for (int i = 0; i < _modelAnimations.size(); i++) {
            // TraceLog(LOG_ERROR, "%s", std::string(_modelAnimation[i].name).c_str());
        }
    }

    void EggRaylib::update(void)
    {
        _animFrame++;
    }

    void EggRaylib::draw(const raylib::Camera camera)
    {
        // draw
        raylib::Vector3 playerPos = raylib::Vector3{
            _currentPos.x * _gridSize + offset.x,
            0,
            _currentPos.y * _gridSize + offset.y};
        _model.Draw(playerPos,
            raylib::Vector3(0, 1, 0), 0,
            raylib::Vector3(_scale, true),
            _tint);
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
