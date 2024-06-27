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
        float gridSize, raylib::Shader &shader, raylib::Color tint) :
        AEntityRaylib(gridSize), worldEgg(egg), _model(model), _tint(tint), _modelAnimations(animations)
    {
        _scale = _gridSize * 0.06;

        _model.materials[1].shader = shader;

        offset = raylib::Vector2(
                Utils::generateRandomFloat(gridSize / 1.3),
                Utils::generateRandomFloat(gridSize / 10) + gridSize / 3);
        _currentPos = raylib::Vector2(worldEgg->getX(), worldEgg->getY());

        _animationIndexes["idle"] = getAnimationIndex({"ground_idle"});
        _animationIndexes["faint"] = getAnimationIndex({"faint"});
        _animationIndexes["sleep"] = getAnimationIndex({"sleep"});
        _animationIndexes["cry"] = getAnimationIndex({"cry"});
    }

    void EggRaylib::update(void)
    {
        _animFrame++;
        if (_isDying) {
            _animatedScale -= _gridSize / 1000.;
        } else if (_animatedScale < _scale) {
            _animatedScale += (_scale - _animatedScale) / 1000. + _gridSize / 1000.;
        }
    }

    void EggRaylib::draw(void)
    {
        raylib::Vector3 playerPos = raylib::Vector3{
            _currentPos.x * _gridSize + offset.x,
            0,
            _currentPos.y * _gridSize + offset.y};
        _model.Draw(playerPos,
            raylib::Vector3(0, 1, 0), 0,
            raylib::Vector3(_animatedScale, true),
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
